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
    defaults = defaults or {}
    for k, v in pairs (defaults) do
        if not self.fields[k] then
            self.fields[k] = v
        end
    end
    return self
end

function description_proto:set_many(list, options)
    if type(list) ~= "table" then
        error(self, list, options)
        return
    end
    for k, v in pairs (list) do
        self:set(k, v, options)
    end
    self:commit()
    return self
end

function description_proto:set(attr, val, options)
    if val == nil and type(attr) == "table" then
        self:set_many(attr, {silent=true})
        return self
    end

    if self.fields[attr] == val or not attr then
        return self
    end

    self.previous[attr] = self.fields[attr]
    self.fields[attr] = val
    
    self.changed = self.changed or {}
    self.changed[attr] = true

    if options and options.silent then
        return self
    end

    self:commit()

    return self
end

function description_proto:has_changed(field)
    if not self.changed then
        return false
    end
    return self.changed[field]
end

function description_proto:any_have_changed(...)
    local arg
    for i = 1, select("#", ...) do
        arg = select(i, ...)
        if self:has_changed(arg) then
            return true
        end
    end
    return false
end

function description_proto:all_have_changed(...)
    local arg
    for i = 1, select("#", ...) do
        arg = select(i, ...)
        if not self:has_changed(arg) then
            return false
        end
    end
    return true
end

function description_proto:check_for_new_changes(was_changed, all_changed, new_changes)
    for k, v in pairs(self.changed) do
        if not was_changed[k] then
            table.insert(all_changed, k)
            new_changes[k] = 1
            was_changed[k] = 1
        end
    end
end

function description_proto:commit(skip_validation)
    if not self.changed or self.committing then
        return self
    end

    if not skip_validation then
        self:validate()
    end

    self.committing = true

    local was_changed = {}
    local all_changed = {}
    local new_changes = {}
    self:check_for_new_changes(was_changed, all_changed, new_changes)
    
    for k, v in ipairs(all_changed) do
        self.events:trigger(v, self.fields[v], self)
        new_changes[v] = nil
        self:check_for_new_changes(was_changed, all_changed, new_changes)
    end
    self.events:trigger("changed", self, self)

    self.changed = new_changes
    self.committing = false

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
    local def
    local def_type = type(definitions)
    if def_type == "string" then
        def = data_store:fetch("definition", definitions)
        if not def then
            warning("Definition " .. definitions .. " does not exist.  Creating empty placeholder")
            def = definition.workon(definitions)
        end
    elseif def_type == "table" then
        if definitions.data_type and definitions.data_type == "definition" then
            def = definitions
        else
            for k, v in pairs(definitions) do
                self:add_definitions(v, false)
                return self
            end
        end
    end

    if not def or self:has_definition(def) then
        return self
    end

    data_store:create("definition_index:"..def.name, self.name, self)

    table.insert(self.definitions, def.name)

    self:set_defaults(def.defaults)

    for k, v in pairs(def.validators) do
        self:add_validator(k, v)
    end

    self.events:merge_from(def.default_events)

    for k, v in pairs(def.extended_from) do
        self:add_definitions(v)
    end

    for k, v in pairs(def.methods) do
        if type(v) ~= "function" or type(k) ~= "string" then
            warning("invalid method in definition table")
            return false
        elseif table_utils.contains_key(self, k) then
            warning("Description method shares a used key in description, aborting assignment.")
        else
            self[k] = v
        end
    end

    def.events:trigger("apply", def, self)

    return self
end

function description_proto:remove_definitions(definitions)

    return self
end

function description_proto:get_definitions()
    return self.definitions
end

function description_proto:has_definition(definition)
    local name = definition

    if type(definition) == "table" and definition.name then
        name = definition.name
    elseif type(definition) == "string" then
        name = definition
    else
        error("Could not determine definition name", 2)
    end

    for k, v in pairs(self.definitions) do
        if v == name then
            return true
        end
    end

    return false
end

description_proto.__index = description_proto

function M.workon(name, definitions)
    local result = M.fetch(name, definitions, suppress)
    if not result then
        return M.create(name, definitions)
    end
    return result
end

function M.fetch(name, definitions, suppress)
    if not name then
        if not suppress then
            error ("Description name must not be nil")
        end
        return false
    end

    local found_desc = data_store:fetch("description", name)

    if found_desc then
        found_desc:set_defaults(defaults)
        found_desc:add_definitions(definitions)
        return found_desc
    end

    return false
end

function M.create(name, definitions)
    if not name then
        name = UUID()
    elseif type(name) == "table" then
        defaults = name
        name = UUID()
    end

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
                                events = event_pump.workon(name .. "_events")
                            }

    setmetatable(new_description, description_proto)
    new_description:set_defaults(defaults)
    new_description:add_definitions(definitions)
    new_description.events:trigger("initialize", new_description, new_description)

    data_store:create("description", name, new_description)

    return new_description
end

return M