-- Collections are groups of similar descriptions
-- Descriptions in a Collection are like rows in a table
-- Only store references

collection = collection or {}

local event_pump = event_pump
local M = collection
local collection_proto = {}

function collection_proto:has(target)

end

function collection_proto:add(target)
    
end

function collection_proto:remove(target)
    
end

collection_proto.__index = collection_proto

local function base_collection()
    return  {
                definitions = {},
                contents = {},
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