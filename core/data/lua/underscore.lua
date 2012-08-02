_ = _ or {}

_.deep_copy = function(table)
    local lookup_table = {}
    local function _copy(table)
        if type(table) ~= "table" then
            return table
        elseif lookup_table[table] then
            return lookup_table[table]
        end
        local new_table = {}
        lookup_table[table] = new_table
        for index, value in pairs(table) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(table))
    end
    return _copy(table)
end

_.shallow_copy = function(table)
	local new_table = {}
	for k,v in pairs(table) do
		new_table[k] = v
	end
	return setmetatable(new_table, getmetatable(table))
end

_.clone = _.shallow_copy

_.extend = function(first, second)
	local new_table = _.shallow_copy(first)

	for k,v in pairs(second) do 
		new_table[k] = v
	end

	return new_table
end

_.merge = _.extend

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

_.select = _.filter

_.every = function (table, iter)
	_.each(table, function(val, key)
		if not iter(val, key) then 
			return false
		end
	end)
	return true
end

_.any = function (table, iter)
	for k, v in pairs(table) do
		if iter(v, k) then
			return true
		end
	end
	return false
end

_.raw_contains = function (table, target)
	for k,v in pairs(table) do
		if rawcompare(v, target) then
			return true
		end
	end
	return false
end

_.max = function (table, iter)
	local val = nil
	iter = iter or math.max
	for k, v in pairs(table) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

_.min = function (table, iter)
	local val = nil
	iter = iter or math.min
	for k, v in pairs(table) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

_.group_by = function (table, iter)
	local results = {}
	for k, v in pairs(table) do
		results[iter(v, k)] = v
	end
	return results
end

