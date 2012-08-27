event_pump = event_pump or {}

definition = definition or {}

local table_utils = table_utils
local M = definition

local definition_proto = {}

function definition_proto:extends(definitions)
    local def
    local def_type = type(definitions)
    if def_type == "string" then
        def = data_store:fetch("definition", definitions)
        if not def then
            print("Definition " .. definitions .. " does not exist. Aborting extend.")
        end
    elseif def_type == "table" then
        if definitions.data_type and definitions.data_type == "definition" then
            def = definitions
        else
            for k, v in pairs(definitions) do
                self:extends(v)
                return self
            end
        end
    end

    if not def or table_utils.contains(self.extended_from, def.name) then
        return self
    end

    table.insert(self.extended_from, def.name)

    return self
end

definition_proto.__index = definition_proto

local function base_definition()
    return  {
                name = "__undefined__",
                data_type = "definition",
                extended_from = {},
                defaults = {},
                validators = {},
                methods = {}
            }
end

function M.workon(name, extends)
    local result = M.fetch(name, extends)
    if not result then
        return M.create(name, extends)
    end
    return result
end

function M.fetch(name, extends)
    if not name then
        error ("Definition name must not be nil")
        return false
    end

    local def = data_store:fetch("definition", name)
    if def and extends then
        def:extends(extends)
    end

    return def
end

function M.create(name, extends)
    if not name then
        error("Definitions must have a name")
    end

    if data_store:has("definition", name) then
        error ("Existing definition found in data_store: ", name)
        return false
    end

    local new_definition = base_definition()
    new_definition.name = name
    new_definition.events = event_pump.workon(name .. "_def_e")
    new_definition.default_events = event_pump.workon(name .. "_def_de")

    setmetatable(new_definition, definition_proto)
    
    data_store:create("definition", name, new_definition)

    if new_definition and extends then
        new_definition:extends(extends)
    end


    return new_definition
end
