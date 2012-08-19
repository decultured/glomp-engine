-- descriptions store state and trigger events based on state change
--
-- Fields:
--     Can store:
--         number, string, boolean, nil (as empty field)
--     Can't store:
--         function, userdata, thread, table
--
-- Definitions:
-- 
-- IDs:
--     Must be unique
--     Can be generated automatically using a pseudo-UUID algorithm

glomp = glomp or {}
glomp.description = glomp.description or {}

local event_pump = event_pump
local data_store = glomp.data_store
local table_util = glomp.table_utils

local M = glomp.description

local description_proto = {}

function description_proto:has(attr)
    return self.attributes[attr] ~= nil
end

function description_proto:set_defaults(defaults)
    defaults = defaults or {}
    for k, v in pairs (defaults) do
        if not self.attributes[tostring(k)] then
            self.attributes[tostring(k)] = v
        end
    end
end

function description_proto:set_many(table, options)
    for k, v in pairs (table) do
        self:set(tostring(k), v, {silent = true})
        self.events:trigger(tostring(k), v, self)
    end
    self.events:trigger("changed", self)
end

function description_proto:set(attr, val, options)
    if val == nil then
        self:set_many(attr)
        return
    end

    if self.attributes[attr] == val or not attr then
        return
    end

    self.previous[attr] = self.attributes[attr]
    self.attributes[attr] = val
    self.changed[attr] = 1

    if options and options.silent then
        return
    end

    self.events:trigger(attr, val, self)
    self.events:trigger("changed", self)
end

function description_proto:apply_to(attr, funct, options)
    self:set(attr, funct(self.attributes[attr]), options)
end

function description_proto:add_to(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] + val, options)
    end
end

function description_proto:multiply(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] * val, options)
    end
end

function description_proto:toggle(attr, options)
    self:set(attr, not self.attributes[attr], options)
end

function description_proto:concat(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] .. val, options)
    end
end

function description_proto:get(attr, default)
    return self.attributes[attr] or default
end

function description_proto:all()
    return self.attributes
end

function description_proto:unset(attr)
    self:set(attr, nil)
end
    
function description_proto:clear(self)
    self.attributes = {}
end

function description_proto:__tostring()
    return self:toJSON()
end

function description_proto:toJSON()
    return json.encode(self.attributes)
end

function description_proto:fromJSON(JSON_data)
    self:set(json.decode(JSON_data))
end

function description_proto:marshal()
    marshal.encode(self.attributes)
end
    
function description_proto:unmarshal(marshalled_data)
    self:set(marshal.decode(marshalled_data))
end

description_proto.__index = description_proto

function M.fetch_or_create(id, defaults)
    local result = self:fetch(id, defaults)
    if not result then
        result = self:create(id, defaults)
    end
    return result
end

function M.fetch(id, defaults)
    if not id then
        error ("Description id must not be nil")
        return false
    end

    local found_desc = data_store:get(id)

    if found_desc then
        self:set_defaults(defaults)
        return found_desc
    end

    return false
end

function M.create(id, defaults)
    if not id then
        id = UUID()
    elseif type(id) == "table" then
        defaults = id
        id = UUID()
    end

    if data_store:has(id) then
        error ("Existing Item Found in data_store: ", id)
        return false
    end

    local new_description = {
                                id = id,
                                previous = {},
                                attributes = {},
                                changed = {}
                            }
    new_description.events = event_pump.create()

    setmetatable(new_description, description_proto)
    new_description:set_defaults(defaults)

    data_store:set(id, new_description)

    return new_description
end

return M