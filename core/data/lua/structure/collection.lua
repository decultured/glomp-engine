-- Collections are groups of similar descriptions
-- Descriptions in a Collection are like rows in a table
-- Only store references

collection = collection or {}

local event_pump = event_pump
local table_utils = table_utils
local M = collection
local collection_proto = {}



function collection_proto:add(target)
    if not target or
        not type(target) == "table" or
        not target.data_type == "description" then
            error("Collections store only definitions")
            return false
    end    

    for k, v in pairs(self.definitions) do
        if not target.has_definition(v.name) then
            error ("target does not have the required definition")
            return false
        end
    end

    table.insert(self.descriptions, target)
end

function collection_proto:add_many(targets)
    for k, v in targets do
        self:add(v)
    end
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

end

function M.fetch(name)
    local coll = data_store:get("collection", name)



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

    set_metatable(new_collection, collection_proto)

    return new_collection
end

return M