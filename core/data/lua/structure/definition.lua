event_pump = event_pump or {}

local M = definition or {}

local definition_proto = {}


-- field definitions are:
-- {
--      field = "fieldname",
--      default = "default value goes here",
--      type = "typename (bool, number, string, description, collection, resource_type, etc)",
--      definitions = [] (list of definition names allowed, used if type is either "description" or "collection")
--      throws_error = true | false
-- }

definition_proto.__index = definition_proto

local function base_definition()
    return  {
                data_type = "definition",
                events = event_pump.create(),
                defaults = {},
                validators = {},
                default_events = event_pump.create(),
            }
end

function M.workon(name)
    local result = M.fetch(name)
    if not result then
        return M.create(name)
    end
    return result
end

function M.fetch(name)
    if not name then
        error ("Definition name must not be nil")
        return false
    end

    return data_store:fetch("definition", name)
end

function M.create(name)
    if not name then
        error("Definitions must have a name")
    end

    if data_store:has("definition", name) then
        error ("Existing Definition Found in data_store: ", name)
        return false
    end

    local new_definition = base_definition()
    new_definition.name = name

    set_metatable(new_definition, definition_proto)
    
    data_store:create("definition", name, new_definition)

    return new_definition
end
