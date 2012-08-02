
glomp = glomp or {}

local _description_proto = {
	has = function (self, attr)
			return self._attributes[attr] ~= nil
		end,

	set = function (self, attr, val, silent)
			self._previous[attr] = self._attributes[attr] 
			self._attributes[attr] = val
			self._changed[attr] = 1
		end,

	get = function (self, attr)
			return self._attributes[attr]
		end,

	unset = function (self, attr)
			self:set(attr, nil)
		end,
	
	clear = function (self)
		
		end,

	on = function (event, callback)
		
		end,

	__tostring = function ()
			json.encode(self._attributes)
		end,

	toJSON = function ()
			json.encode(self._attributes)
		end,

	fromJSON = function (JSON_data)
			self.set(json.decode(JSON_data))
		end,

	marshal = function ()
		 	marshal.encode(self._attributes)
		end,
	unmarshal = function (marshalled_data)
			self.set(marshal.decode(marshalled_data))
		end
}

_description_proto.__index = _description_proto

-- Descriptions have state
glomp.Description = {
	new = function (initial)
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
		end,
}

-- Collections are groups of similar descriptions
glomp.collection = {}

-- Compositions are groups of dissimilar but related descriptions
glomp.composition = {}

-- Roles allow descriptions to do things, but have no state themselves
glomp.Role = {}