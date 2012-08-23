event_pump = event_pump or {}

local M = definition or {}

local definition_proto = {}

local need = {
    field:
    default:
    type:
}

definition_proto.__index = definition_proto

local function base_definition()
    return  {
                id = UUID(),
                events = event_pump.create(),
                needs = {},
                wants = {},
            }
end

function M.workon(name)
    local result = M.fetch(name)
    if not result then
        M.create(name)
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
        name = UUID()
    end

    if data_store:has("definition", name) then
        error ("Existing Item Found in data_store: ", name)
        return false
    end

    local new_definition = base_definition()

    set_metatable(new_definition, definition_proto)
    
    data_store:create("definition", name, new_definition)

    return new_definition
end
