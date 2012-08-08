
-- nil, boolean, number, string, function, userdata, thread, table

local _description_proto = {}

function _description_proto:has(attr)
	return self._attributes[attr] ~= nil
end

function _description_proto:set_many(table, options)
	if type(table) == "table" then
		for k, v in pairs (table) do
			if type(v) == "table" then
				error("Values set to a description must only be basic types")
			end

			self:set(tostring(k), v, {silent = true})
			self._event_pump:trigger(tostring(k), v, self)
		end
	end
	self._event_pump:trigger("changed", self)
end

function _description_proto:set(attr, val, options)
	if val == nil then
		self:set_many(attr)
		return
	end

	local val_type = type(val)

	if val_type == "number" or val_type == "string" or val_type == "boolean" then
		if self._attributes[attr] == val or not attr then
			return
		end
		self._previous[attr] = self._attributes[attr]
		self._attributes[attr] = val
		self._changed[attr] = 1

		if options and options.silent then
			return
		end
	elseif val_type == "table" then
		self:set_many(val)
		return
	else
		error("Descriptions can only store numbers, strings or booleans, " .. val_type .. " was provided.")
		return
	end
	self._event_pump:trigger(attr, val, self)
	self._event_pump:trigger("changed", self)
end

function _description_proto:apply_to(attr, funct, options)
	self:set(attr, funct(self._attributes[attr]), options)
end

function _description_proto:add_to(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] + val, options)
	end
end

function _description_proto:multiply(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] * val, options)
	end
end

function _description_proto:concat(attr, val, options)
	if self._attributes[attr] then
		self:set(attr, self._attributes[attr] .. val, options)
	end
end

function _description_proto:get(attr, default)
	return self._attributes[attr] or default
end

function _description_proto:all()
	return self._attributes
end

function _description_proto:unset(attr)
	self:set(attr, nil)
end
	
function _description_proto:clear(self)
	
end

function _description_proto:on(event, callback)
	self._event_pump:on(event, callback)
end

function _description_proto:off(event, callback)
	self._event_pump:off(event, callback)
end

function _description_proto:when(event, callback, truth_check, ...)
	self._event_pump:when(event, callback, truth_check, ...)
end

function _description_proto:when_equals(event, callback, val)
	self._event_pump:when_equals(event, callback, val)
end

function _description_proto:when_not_equals(event, callback, val)
	self._event_pump:when_not_equals(event, callback, val)
end

function _description_proto:when_greater_than(event, callback, val)
	self._event_pump:when_greater_than(event, callback, val)
end

function _description_proto:when_less_than(event, callback, val)
	self._event_pump:when_less_than(event, callback, val)
end

function _description_proto:__tostring()
	return json.encode(self._attributes)
end

function _description_proto:toJSON()
	return json.encode(self._attributes)
end

function _description_proto:fromJSON(JSON_data)
	self:set(json.decode(JSON_data))
end

function _description_proto:marshal()
 	marshal.encode(self._attributes)
end
	
function _description_proto:unmarshal(marshalled_data)
	self:set(marshal.decode(marshalled_data))
end

_description_proto.__index = _description_proto

-- Descriptions have state
Description = {}

function Description.new(name, initial, options)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		options = initial
		initial = name
		name = UUID()
	end

	print("New object: "..name)
	local new_description = {
				_name = name,
				_previous = {},
				_attributes = {},
				_changed = {},
				_event_pump = EventPump.new(name)
			}
	setmetatable(new_description, _description_proto)
	if initial then
		new_description:set_many(initial, {silent = true})
	end
	return new_description
end

-- Collections are groups of similar descriptions
-- Descriptions in a Collection are like rows in a table
-- Only store references
Collection = {}

-- Compositions are groups of dissimilar but related descriptions
-- Descriptions in a Composition are like join tables
-- Only store references
Composition = {}

-- Contexts apply roles to Descriptions, Collections, and/or Compositions and act upon them
Contexts = {}

-- Roles allow descriptions to do things, but have no state themselves
Role = {}
