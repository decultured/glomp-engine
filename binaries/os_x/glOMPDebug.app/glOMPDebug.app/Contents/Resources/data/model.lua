
glomp = glomp or {}

glomp.Model = {
	_previous = {},
	_attributes = {},
	_changed = {},

	has = function (attr)
			return attributes[attr] not nil
		end

	set = function (attr, val)
			previous[attr] = attributes[attr] 
			attributes[attr] = val
			changed[attr] = 1
		end

}