local _event_pump_proto = {}

function _event_pump_proto:on(event, callback)
	print ("On : ", event)
	local list = self._callbacks[event] or {}
	list[#list + 1] = callback
	self._callbacks[event] = list
end

function _event_pump_proto:off(event, callback)
	print ("Off : ", event)
	local list = self._callbacks[event] or {}
	for k, v in pairs(list) do
		if v == callback then
			list[k] = nil
		end
	end
end

function _event_pump_proto:trigger(event, data)
	local list = self._callbacks[event] or {}
	for k, v in pairs(list) do
		if type(v) == "function" then
			v(data)
		end
	end
end

_event_pump_proto.__index = _event_pump_proto

EventPump = {}

function EventPump.new(name)
	local new_event_pump = {
				_callbacks = {},
			}

	setmetatable(new_event_pump, _event_pump_proto)
	return new_event_pump
end
