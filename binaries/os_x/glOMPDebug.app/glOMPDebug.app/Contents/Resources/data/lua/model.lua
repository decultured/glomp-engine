
glomp = glomp or {}

glomp.Model = {
	_previous = {},
	_attributes = {},
	_changed = {},

	has = function (attr)
			return attributes[attr] ~= nil
		end,

	set = function (self, attr, val)
			self._previous[attr] = self._attributes[attr] 
			self._attributes[attr] = val
			self._changed[attr] = 1
		end,

	get = function (self, attr)
			return self._attributes[attr]
		end


}