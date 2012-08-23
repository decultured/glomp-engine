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

description = description or {}

local event_pump = event_pump
local data_store = data_store
local table_util = table_utils

local M = description

local description_proto = {}

function description_proto:has(attr)
    return self.attributes[attr] ~= nil
end

function description_proto:set_defaults(defaults)
    if not defaults then
        return false
    end

    for k, v in pairs (defaults) do
        if not self.attributes[k] then
            self.attributes[k] = v
        end
    end
    return self
end

function description_proto:set_many(table, options)
    for k, v in pairs (table) do
        self:set(k, v, {silent = true})
        self.events:trigger(k, v, self)
    end
    self.events:trigger("changed", self)
    return self
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

    return self
end

function description_proto:get(attr, default)
    return self.attributes[attr] or default
end

function description_proto:all()
    return self.attributes
end

function description_proto:apply_to(attr, funct, options)
    self:set(attr, funct(self.attributes[attr]), options)
    return self
end

function description_proto:add_to(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] + val, options)
    end
    return self
end

function description_proto:multiply(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] * val, options)
    end
    return self
end

function description_proto:toggle(attr, options)
    self:set(attr, not self.attributes[attr], options)
    return self
end

function description_proto:concat(attr, val, options)
    if self.attributes[attr] then
        self:set(attr, self.attributes[attr] .. val, options)
    end
    return self
end

function description_proto:unset(attr)
    self:set(attr, nil)
    return self
end
    
function description_proto:clear(self)
    self.attributes = {}
    return self
end

function description_proto:__tostring()
    return self:toJSON()
end

function description_proto:toJSON()
    return json.encode(self.attributes)
end

function description_proto:fromJSON(JSON_data)
    self:set(json.decode(JSON_data))
    return self
end

function description_proto:marshal()
    return marshal.encode(self.attributes)
end
    
function description_proto:unmarshal(marshalled_data)
    self:set(marshal.decode(marshalled_data))
end

function description_proto:add_definitions(definitions)
    local def_type = type(definitions)
    if def_type == "string" then
        

    return self
end

function description_proto:remove_definitions(definitions)

    return self
end

function get_definitions()
    return self.definitions
end

function has_definition(definition)
    
end

description_proto.__index = description_proto

function M.workon(name, defaults, definitions)
    local result = M.fetch(name, defaults, definitions)
    if not result then
        result = M.create(name, defaults, definitions)
    end
    return result
end

function M.fetch(name, defaults, definitions)
    if not name then
        error ("Description name must not be nil")
        return false
    end

    local found_desc = data_store:fetch("description", name)

    if found_desc then
        found_desc:set_defaults(defaults)
        return found_desc
    end

    return false
end

function M.create(name, defaults, definitions)
    if not name then
        name = UUID()
    elseif type(name) == "table" then
        defaults = name
        name = UUID()
    end

    print ("New Description: ", name)

    if data_store:has("description", name) then
        error ("Existing Item Found in data_store: ", name)
        return false
    end

    local new_description = {
                                name = name,
                                previous = {},
                                attributes = {},
                                changed = {},
                                definitions = {},
                                events = event_pump.create(name)            
                            }

    setmetatable(new_description, description_proto)
    new_description:set_defaults(defaults)

    data_store:create("description", name, new_description)

    return new_description
end

return M