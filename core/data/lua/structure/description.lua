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
    return self.fields[attr] ~= nil
end

function description_proto:set_defaults(defaults)
    if not defaults then
        return false
    end

    for k, v in pairs (defaults) do
        if not self.fields[k] then
            self.fields[k] = v
        end
    end
    return self
end

function description_proto:set_many(table, options)
    for k, v in pairs (table) do
        self:set(k, v, {silent = true})
    end
    self:commit()
    return self
end

function description_proto:set(attr, val, options)
    if val == nil then
        self:set_many(attr)
        return
    end

    if self.fields[attr] == val or not attr then
        return
    end

    self.previous[attr] = self.fields[attr]
    self.fields[attr] = val
    
    self.changed = self.changed or {}
    self.changed[attr] = true

    if options and options.silent then
        return
    end

    self:commit()

    return self
end

function description_proto:commit(skip_validation)
    if not self.changed then
        return self
    end

    if not skip_validation then
        self:validate()
    end

    for k, v in pairs(self.changed) do
        self.events:trigger(k, self.fields[k], self)
    end
    self.events:trigger("changed", self)

    return self
end

function description_proto:validate()

    return self
end

function description_proto:get(attr, default)
    return self.fields[attr] or default
end

function description_proto:all()
    return self.fields
end

function description_proto:apply_to(attr, funct, options)
    self:set(attr, funct(self.fields[attr]), options)
    return self
end

function description_proto:add_to(attr, val, options)
    if self.fields[attr] then
        self:set(attr, self.fields[attr] + val, options)
    end
    return self
end

function description_proto:multiply(attr, val, options)
    if self.fields[attr] then
        self:set(attr, self.fields[attr] * val, options)
    end
    return self
end

function description_proto:toggle(attr, options)
    self:set(attr, not self.fields[attr], options)
    return self
end

function description_proto:concat(attr, val, options)
    if self.fields[attr] then
        self:set(attr, self.fields[attr] .. val, options)
    end
    return self
end

function description_proto:unset(attr)
    self:set(attr, nil)
    return self
end
    
function description_proto:clear(self)
    self.fields = {}
    return self
end

function description_proto:__tostring()
    return self:toJSON()
end

function description_proto:toJSON()
    return json.encode(self.fields)
end

function description_proto:fromJSON(JSON_data)
    self:set(json.decode(JSON_data))
    return self
end

function description_proto:marshal()
    return marshal.encode(self.fields)
end
    
function description_proto:unmarshal(marshalled_data)
    self:set(marshal.decode(marshalled_data))
end

function description_proto:add_validator(value, validation_function)
    if type(validation_function) ~= "function" then
        return self
    end

    self.validators[value] = self.validators[value] or {}

    table.insert(self.validators[value], validation_function)

    return self
end

function description_proto:add_definitions(definitions)
    local definition
    local def_type = type(definitions)
    if def_type == "string" then
        local definition = data_store.fetch("definition", definitions)
    elseif def_type == "table" then
        if definitions.create then
            definition = definitions
        else
            for k, v in pairs(definitions) do
                self:add_definitions(v)
            end
        end
    end

    if not definition then
        return self
    end

    table.insert(self.definitions, definition)

    self:set_defaults(definition.defaults)

    for k, v in definition.validators do
        self:add_validator(k, v)
    end

    self.events.merge_from(definition.default_events)

    return self
end

function description_proto:remove_definitions(definitions)

    return self
end

function get_definitions()
    return self.definitions
end

function has_definition(definition)
    local name = definition

    if type(definition) == "table" and definition.name then
        name = definition.name
    else
        error("Could not determine definition name", 2)
    end

    for k, v in pairs(self.definitions) do
        if v.name == name then
            return true
        end
    end

    return false
end

description_proto.__index = description_proto

function M.workon(name, defaults, definitions)
    local result = M.fetch(name, defaults, definitions)
    if not result then
        return M.create(name, defaults, definitions)
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
                                data_type = "description",
                                name = name,
                                previous = {},
                                fields = {},
                                changed = nil,
                                definitions = {},
                                events = event_pump.create(name)            
                            }

    setmetatable(new_description, description_proto)
    new_description:set_defaults(defaults)

    data_store:create("description", name, new_description)

    return new_description
end

return M