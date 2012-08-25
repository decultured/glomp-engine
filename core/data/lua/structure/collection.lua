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
        return table_utils[v](self.descriptions, ...)
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
        if not target:has_definition(v) then
            error ("Target " .. target.name .. " does not have the required definition: " .. v)
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
    local desc = self.descriptions
    local item 

    for i = 1,#desc do
        item = desc[i]
        item.events:trigger(event, data, item)
    end
end

function collection_proto:trigger_all_until(event, data)
    local desc = self.descriptions
    local item 

    for i = 1,#desc do
        item = desc[i]
        if item.events:trigger(event, data, item) then
            return true
        end
    end
end

function collection_proto:reverse_trigger_all(event, data)
    local desc = self.descriptions
    local item 

    for i = #desc,1,-1 do
        item = desc[i]
        item.events:trigger(event, data, item)
    end
end

function collection_proto:reverse_trigger_all_until(event, data)
    local desc = self.descriptions
    local item 

    for i = #desc,1,-1 do
        item = desc[i]
        if item.events:trigger(event, data, item) then
            return true
        end
    end
end

function collection_proto:add_definitions(definitions)
    local def
    local def_type = type(definitions)
    if def_type == "string" then
        if not table_utils.contains(self.definitions, definitions) then
            table.insert(self.definitions, definitions)
        end
        return self
    elseif def_type == "table" then
        if definitions.data_type and definitions.data_type == "definition" then
            self:add_definitions(definitions.name)
        else
            for k, v in pairs(definitions) do
                self:add_definitions(v)
            end
        end
    end
    return self
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

function M.workon(name, definitions)
    local coll = M.fetch(name, definitions)
    if not coll then
        return M.create(name, definitions)
    end
    return coll
end

function M.fetch(name, definitions)
    if not name then
        error("Must supply a name for 'fetch'")
        return nil
    end

    local coll = data_store:fetch("collection", name)
    if coll then
        coll:add_definitions(definitions)
    end

    return coll
end

function M.create(name, definitions)
    if not name then
        name = UUID()
    end

    if data_store:has("collection", name) then
        error("Collection: " .. name .. " exists.", 2)
        return false
    end

    local new_collection = base_collection()

    setmetatable(new_collection, collection_proto)
    new_collection.name = name

    new_collection:add_definitions(definitions)

    return new_collection
end

return M