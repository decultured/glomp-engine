
glomp = glomp or {}

local _description_proto = {}

function _description_proto:has(attr)
	return self._attributes[attr] ~= nil
end

function _description_proto:set(attr, val, silent)
	self._previous[attr] = self._attributes[attr] 
	self._attributes[attr] = val
	self._changed[attr] = 1
end

function _description_proto:get(attr)
	return self._attributes[attr]
end

function _description_proto:remove(attr)
	self:set(attr, nil)
end
	
function _description_proto:clear(self)

end

function _description_proto:on(event, callback)
		
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
glomp.Description = {}

function glomp.Description.new(initial)
	local new_description = {
				_previous = {},
				_attributes = {},
				_changed = {},
			}
	setmetatable(new_description, _description_proto)
	if initial then
		-- TODO
		-- new_description:set(initial, silent)
	end
	return new_description
end

-- Collections are groups of similar descriptions
glomp.collection = {}

-- Compositions are groups of dissimilar but related descriptions
glomp.composition = {}

-- Roles allow descriptions to do things, but have no state themselves
glomp.Role = {}