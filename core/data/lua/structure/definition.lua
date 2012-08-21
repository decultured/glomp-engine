glomp = glomp or {}
glomp.event_pump = glomp.event_pump or {}

local M = glomp.definition or {}

local definition_proto = {}

definition_proto.__index = definition_proto

local function base_description()
    return  {
                id = UUID(),
                
                events = event_pump.create()
            }
end

function M.fetch_or_create()

end

function M.fetch()

end

function M.create(name)
    if not name then
        name = UUID()
    end

    local new_definition = base_definition()

    set_metatable(new_definition, definition_proto)

    return new_definition
end
