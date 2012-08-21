glomp = glomp or {}
glomp.event_pump = glomp.event_pump or {}

local data_store = glomp.data_store
local table_utils = glomp.table_utils

local M = glomp.event_pump

local event_pump_proto = {}

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

local function _between(data, min, max)
	return min < param < max
end

local function _not_between(data, min, max)
	return not (min < param < max)
end

function event_pump_proto:on(event, callback)
	local list = self.callbacks[event] or {}
	table.insert(list, { 
			callback = callback
		})
	self.callbacks[event] = list
end

function event_pump_proto:when(event, callback, truth_check, ...)
	local list = self.callbacks[event] or {}
	table.insert(list, { 
			callback = callback,
			truth_check = truth_check,
			params = ...
		})
	self.callbacks[event] = list
end

function event_pump_proto:when_not_equals(event, callback, val)
	self:when(event, callback, _not_equals, val)
end

function event_pump_proto:when_equals(event, callback, val)
	self:when(event, callback, _equals, val)
end

function event_pump_proto:when_greater_than(event, callback, val)
	self:when(event, callback, _greater_than, val)
end

function event_pump_proto:when_less_than(event, callback, val)
	self:when(event, callback, _less_than, val)
end

function event_pump_proto:when_between(event, callback, min, max)
	self:when(event, callback, _between, min, max)
end

function event_pump_proto:when_not_between(event, callback, min, max)
	self:when(event, callback, _not_between, min, max)
end

function event_pump_proto:off(event, callback)
	local list = self.callbacks[event] or {}
	for k, v in pairs(list) do
		if v.callback == callback then
			table.remove(list,k)
		end
	end
end

function event_pump_proto:trigger(event, data, caller)
	local list = self.callbacks[event] or {}
	for k, v in pairs(list) do
		if v.callback and type(v.callback) == "function" then
			if not v.truth_check or v.truth_check(data, v.params) then
				v.callback(data, caller)
			end
		end
	end
end

function event_pump_proto:clone(name)
	local new_event_pump = { callbacks = {} }

	for k, v in pairs(self.callbacks) do
		new_event_pump.callbacks[k] = {}
		local insnamee = new_event_pump.callbacks[k]
		for k, v in pairs(v) do
			table.insert(insnamee, v)
		end
	end

	setmetatable(new_event_pump, event_pump_proto)
	return new_event_pump
end

event_pump_proto.__index  = event_pump_proto

function M.fetch_or_create(name)
	local event_pump = M.fetch(name);
	if not event_pump then
		return M.create(name)
	end
	return event_pump
end

function M.fetch(name)
	if not name then
		error ("Event Pump name must not be nil")
		return false
	end

	return data_store:get("event", name)
end

local function build_event(name)
	if not name then
		name = UUID()
	end

	local new_event_pump =  { 
								name = name,
								callbacks = {} 
							}
	setmetatable(new_event_pump, event_pump_proto)

	return new_event_pump
end

function M.create(name)
	local new_event_pump = build_event(name)
	return data_store:create("event", name, new_event_pump)
end

data_store:add_builder("event", build_event)

return M