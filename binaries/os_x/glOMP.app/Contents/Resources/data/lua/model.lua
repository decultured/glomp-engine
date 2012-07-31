
glomp = glomp or {}

glomp.Model = {
	_previous = {},
	_attributes = {},
	_changed = {},

	has = function (attr)
			if attributes[attr] not nil then
				return true
			end
			return false
		end,

	set = function (attr, val)
			previous[attr] = attributes[attr] 
			attributes[attr] = val
			changed[attr] = 1
		end

}