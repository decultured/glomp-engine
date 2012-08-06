
local _description_proto = {}

function _description_proto:has(attr)
	return self._attributes[attr] ~= nil
end

function _description_proto:set(attr, val, options)
	if not attr then
		return
	end
	if type(attr) == "table" then
		for k, v in pairs (attr) do
			if type(v) == "table" then
				error("Values set to a description must only be basic types")
			end

			self:set(tostring(k), v, options)
		end
		return
	else
		self._previous[attr] = self._attributes[attr] 
		self._attributes[attr] = val
		self._changed[attr] = 1
		self._event_pump:trigger("change" .. ":" .. attr, val)
	end

end

function _description_proto:get(attr, default)
	if self._attributes[attr] then
		return self._attributes[attr]
	else 
		return default
	end
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
	if type(name) == "table" then
		options = initial
		initial = name
	end

	local new_description = {
				_previous = {},
				_attributes = {},
				_changed = {},
				_event_pump = EventPump.new(name)
			}
	setmetatable(new_description, _description_proto)
	if initial then
		new_description:set(initial, true)
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
