local function _equals(data, param)
	return data == param
end

local function _not_equals(data, param)
	return data ~= param
end

local function _greater_than(data, param)
	return data > param
end

local function _less_than(data, param)
	return data < param
end

local _event_pump_proto = {}

function _event_pump_proto:on(event, callback)
	local list = self._callbacks[event] or {}
	table.insert(list, { 
			callback = callback
		})
	self._callbacks[event] = list
end

function _event_pump_proto:when(event, callback, truth_check, ...)
	local list = self._callbacks[event] or {}
	table.insert(list, { 
			callback = callback,
			truth_check = truth_check,
			params = ...
		})
	self._callbacks[event] = list
end

function _event_pump_proto:when_not_equals(event, callback, val)
	self:when(event, callback, _not_equals, val)
end

function _event_pump_proto:when_equals(event, callback, val)
	self:when(event, callback, _equals, val)
end

function _event_pump_proto:when_greater_than(event, callback, val)
	self:when(event, callback, _greater_than, val)
end

function _event_pump_proto:when_less_than(event, callback, val)
	self:when(event, callback, _less_than, val)
end

function _event_pump_proto:off(event, callback)
	local list = self._callbacks[event] or {}
	for k, v in pairs(list) do
		if v.callback == callback then
			table.remove(list,k)
		end
	end
end

function _event_pump_proto:trigger(event, data, caller)
	local list = self._callbacks[event] or {}
	for k, v in pairs(list) do
		if v.callback and type(v.callback) == "function" then
			if not v.truth_check or v.truth_check(data, v.params) then
				v.callback(data, caller)
			end
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
