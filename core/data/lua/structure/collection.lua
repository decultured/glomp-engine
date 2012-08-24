-- Collections are groups of similar descriptions
-- Descriptions in a Collection are like rows in a table
-- Only store references

collection = collection or {}

local event_pump = event_pump
local table_utils = table_utils
local M = collection
local collection_proto = {}

local imports = {"each", "map", "reduce", "find", "filter", "select", "every", "any", "contains", "raw_contains", "max", "min", "group_by"}

for k, v in pairs(imports) do
    collection_proto[v] = function (self, ...)
        self.descriptions = table_utils[v](self.descriptions, ...)
        return self
    end
end

function collection_proto:add(target)
    if not target or
        not type(target) == "table" or
        not target.data_type == "description" then
            print (target)
            error("Collections store only descriptions")
            return false
    end

    for k, v in pairs(self.definitions) do
        if not target.has_definition(v.name) then
            error ("target does not have the required definition")
            return false
        end
    end

    table.insert(self.descriptions, target)

    self.events:trigger("add", target, self)
end

function collection_proto:add_many(targets)
    for k, v in targets do
        self:add(v)
    end
end

function collection_proto:remove(target)
    for k, v in ipairs(self.descriptions) do
        if v == target then
            table.remove(self.descriptions, k)
            self.events:trigger("remove", target, self)
        end
    end
end

function collection_proto:clear()
    for k, v in ipairs(self.descriptions) do
        self.events:trigger("remove", v, self)
        self.descriptions[k] = nil
    end
    self.descriptions = {}
    self.events:trigger("reset", self, self)
end

function collection_proto:trigger_all(event, data)
    self:each(function (item) 
        item.events:trigger(event, data, item)
    end)
end

collection_proto.__index = collection_proto

local function base_collection()
    return  {
                data_type = "collection",
                definitions = {},
                descriptions = {},
                events = event_pump.create()
            }
end

function M.workon(name)
    local coll = M.fetch(name)
    if not coll then
        return M.create(name)
    end
    return coll
end

function M.fetch(name)
    if not name then
        error("Must supply a name for 'fetch'")
        return nil
    end

    return data_store:fetch("collection", name)
end

function M.create(name)
    if not name then
        name = UUID()
    end

    if data_store:has("collection", name) then
        error("Collection: " .. name .. " exists.", 2)
        return false
    end

    local new_collection = base_collection()

    setmetatable(new_collection, collection_proto)

    return new_collection
end

return M