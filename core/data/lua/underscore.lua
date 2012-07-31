_ = _ or {}

_.deepcopy = function(object)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for index, value in pairs(object) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end

_.extend = function(first, second)
	local new_table = _.deepcopy(first)

	for k,v in pairs(second) do 
		new_table[k] = v
	end

	return new_table
end

_.each = function(table, iter)
	for k,v in pairs(table) do 
		iter(v, k)
	end
end

_.map = function(table, iter)
	local results = {}
	_.each(table, function(val, key)
			results[#results + 1] = iter(val, key)
		end)
	return results
end

_.reduce = function (table, iter, memo)
	_.each(table, function (val, key)
		memo = iter(val, key, memo)
	end)
	return memo
end

_.find = function (table, iter)
	
	for k,v in pairs(table) do 
		if iter(v, k) then
			return v
		end
	end
	return nil
end


_.filter = function (table, iter)
	local results = {}
	_.each(table, function(val, key)
		if iter(val, key) then 
			results[#results + 1] = val
		end
	end)
	return results
end

