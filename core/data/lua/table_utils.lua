glomp = glomp or {}
glomp.table_utils = glomp.table_utils or {}
local _g_table_utils = glomp.table_utils

_g_table_utils.deep_copy = function(table)
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

_g_table_utils.shallow_copy = function(table)
	local new_table = {}
	table = table or {}
	for k,v in pairs(table) do
		new_table[k] = v
	end
	return new_table
end

_g_table_utils.clone = _g_table_utils.shallow_copy

_g_table_utils.extend = function(first, second)
	local new_table = _g_table_utils.shallow_copy(first) or {}
	second = second or {}
	for k,v in pairs(second) do 
		new_table[k] = v
	end

	return new_table
end

_g_table_utils.set_defaults = function (table, defaults)
	defaults = defaults or {}
	table = table or {}
	for k, v in pairs (defaults) do
		if not table[k] then
			table[k] = v
		end
	end
	return table
end

_g_table_utils.extend_original = function (table, second)
	second = second or {}
	table = table or {}
	for k, v in pairs (second) do
		table[k] = v
	end
	return table
end

_g_table_utils.merge = _g_table_utils.extend

_g_table_utils.add = function(table, val)
	table.insert(val)
end

_g_table_utils.remove_one = function(table, target)
	table = table or {}
	for k,v in pairs(table) do
		if v == target then
			table[k] = nil
			table.remove(table, k)
			return true
		end
	end
	return false
end

_g_table_utils.remove_all = function(table, target)
	local found = false
	table = table or {}
	for k,v in pairs(table) do
		if v == target and type(k) == number then
			table[k] = nil
			table.remove(table, k)
			found = true
		end
	end
	return found
end

_g_table_utils.raw_remove_one = function(table, target)
	table = table or {}
	for k,v in pairs(table) do
		if raw_compare(v, val) then
			table[k] = nil
			table.remove(table, k)
			return true
		end
	end
	return false
end

_g_table_utils.raw_remove_all = function(table, target)
	local found = false
	table = table or {}
	for k,v in pairs(table) do
		if raw_compare(v, target) then
			table[k] = nil
			table.remove(table, k)
			found = true
		end
	end
	return found
end

_g_table_utils.each = function(table, iter)
	table = table or {}
	for k,v in pairs(table) do 
		iter(v, k)
	end
end

_g_table_utils.call_each = function(table, method_name, ...)
	table = table or {}
	for k,v in pairs(table) do 
		v[method_name](v, ...)
	end
end

_g_table_utils.map = function(table, iter)
	local results = {}
	_g_table_utils.each(table, function(val, key)
			results[#results + 1] = iter(val, key)
		end)
	return results
end

_g_table_utils.reduce = function (table, iter, memo)
	_g_table_utils.each(table, function (val, key)
		memo = iter(val, key, memo)
	end)
	return memo
end

_g_table_utils.find = function (table, iter)
	table = table or {}
	for k,v in pairs(table) do 
		if iter(v, k) then
			return v
		end
	end
	return nil
end

_g_table_utils.filter = function (table, iter)
	local results = {}
	_g_table_utils.each(table, function(val, key)
		if iter(val, key) then 
			results[#results + 1] = val
		end
	end)
	return results
end

_g_table_utils.select = _g_table_utils.filter

_g_table_utils.every = function (table, iter)
	_g_table_utils.each(table, function(val, key)
		if not iter(val, key) then 
			return false
		end
	end)
	return true
end

_g_table_utils.any = function (table, iter)
	table = table or {}
	for k, v in pairs(table) do
		if iter(v, k) then
			return true
		end
	end
	return false
end

_g_table_utils.contains = function (table, target)
	table = table or {}
	for k,v in pairs(table) do
		if v == target then
			return true
		end
	end
	return false
end

_g_table_utils.raw_contains = function (table, target)
	table = table or {}
	for k,v in pairs(table) do
		if rawcompare(v, target) then
			return true
		end
	end
	return false
end

_g_table_utils.max = function (table, iter)
	local val = nil
	iter = iter or math.max
	table = table or {}
	for k, v in pairs(table) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

_g_table_utils.min = function (table, iter)
	local val = nil
	iter = iter or math.min
	table = table or {}
	for k, v in pairs(table) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

_g_table_utils.group_by = function (table, iter)
	local results = {}
	table = table or {}
	for k, v in pairs(table) do
		results[iter(v, k)] = v
	end
	return results
end

