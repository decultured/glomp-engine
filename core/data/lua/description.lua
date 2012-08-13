-- Descriptions store state and trigger events based on state change
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

glOMP = glOMP or {}
local _g_table_utils = glOMP.table_utils

local _description_meta = {}

function _description_meta:has(attr)
	return self._attributes[attr] ~= nil
end

function _description_meta:set_defaults(defaults)
	defaults = defaults or {}
	for k, v in pairs (defaults) do
		if not self._attributes[tostring(k)] then
			self._attributes[tostring(k)] = v
		end
	end
end

function _description_meta:set_many(table, options)
	for k, v in pairs (table) do
		self:set(tostring(k), v, {silent = true})
		self._event_pump:trigger(tostring(k), v, self)
	end
	self._event_pump:trigger("changed", self)
end

function _description_meta:set(attr, val, options)
	if val == nil then
		self:set_many(attr)
		return
	end

	if self._attributes[attr] == val or not attr then
		return
	end

	self._previous[attr] = self._attributes[attr]
	self._attributes[attr] = val
	self._changed[attr] = 1

	if options and options.silent then
		return
	end

	self._event_pump:trigger(attr, val, self)
	self._event_pump:trigger("changed", self)
end

function _description_meta:apply_to(attr, funct, options)
	self:set(attr, funct(self._attributes[attr]), options)
end

function _description_meta:add_to(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] + val, options)
	end
end

function _description_meta:multiply(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] * val, options)
	end
end

function _description_meta:toggle(attr, options)
	self:set(attr, not self._attributes[attr], options)
end

function _description_meta:concat(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] .. val, options)
	end
end

function _description_meta:get(attr, default)
	return self._attributes[attr] or default
end

function _description_meta:all()
	return self._attributes
end

function _description_meta:unset(attr)
	self:set(attr, nil)
end
	
function _description_meta:clear(self)
	self._attributes = {}
end

function _description_meta:on(event, callback)
	self._event_pump:on(event, callback)
end

function _description_meta:off(event, callback)
	self._event_pump:off(event, callback)
end

function _description_meta:when(event, callback, truth_check, ...)
	self._event_pump:when(event, callback, truth_check, ...)
end

function _description_meta:when_equals(event, callback, val)
	self._event_pump:when_equals(event, callback, val)
end

function _description_meta:when_not_equals(event, callback, val)
	self._event_pump:when_not_equals(event, callback, val)
end

function _description_meta:when_greater_than(event, callback, val)
	self._event_pump:when_greater_than(event, callback, val)
end

function _description_meta:when_less_than(event, callback, val)
	self._event_pump:when_less_than(event, callback, val)
end

function _description_meta:when_between(event, callback, val)
	self._event_pump:when_between(event, callback, val)
end

function _description_meta:when_not_between(event, callback, val)
	self._event_pump:when_not_between(event, callback, val)
end

function _description_meta:__tostring()
	return json.encode(self._attributes)
end

function _description_meta:toJSON()
	return json.encode(self._attributes)
end

function _description_meta:fromJSON(JSON_data)
	self:set(json.decode(JSON_data))
end

function _description_meta:marshal()
 	marshal.encode(self._attributes)
end
	
function _description_meta:unmarshal(marshalled_data)
	self:set(marshal.decode(marshalled_data))
end

_description_meta.__index = _description_meta

glOMP.Description = glOMP.Description or {}
glOMP.EventPump = glOMP.EventPump or {}

glOMP.store = glOMP.store or {}
glOMP.store.descriptions = glOMP.store.descriptions or {}
local _g_descs = glOMP.store.descriptions

function glOMP.Description:load(name, defaults)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		defaults = name
		name = UUID()
	end

	if _g_descs[name] then
		print ("Existing Description Found: " .. name)
		return _g_descs[name]
	end

	print("New Description: "..name)
	local new_description = _g_table_utils.extend(self, {
				_name = name,
				_previous = {},
				_attributes = {},
				_changed = {},
				_event_pump = glOMP.EventPump.load(name)
			})

	setmetatable(new_description, _description_meta)
	new_description:set_defaults(defaults)

	_g_descs[name] = new_description

	return new_description
end

function glOMP.Description:extend(mixin)
	return _g_table_utils.extend(self, mixin)
end