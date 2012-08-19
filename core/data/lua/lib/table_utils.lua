glomp = glomp or {}
glomp.table_utils = glomp.table_utils or {}
local M = glomp.table_utils

M.deep_copy = function(table)
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

M.shallow_copy = function(table)
	local new_table = {}
	table = table or {}
	for k,v in pairs(table) do
		new_table[k] = v
	end
	return new_table
end

M.clone = M.shallow_copy

M.extend = function(first, second)
	local new_table = M.shallow_copy(first) or {}
	second = second or {}
	for k,v in pairs(second) do 
		new_table[k] = v
	end

	return new_table
end

M.set_defaults = function (table, defaults)
	defaults = defaults or {}
	table = table or {}
	for k, v in pairs (defaults) do
		if not table[k] then
			table[k] = v
		end
	end
	return table
end

M.extend_original = function (table, second)
	second = second or {}
	table = table or {}
	for k, v in pairs (second) do
		table[k] = v
	end
	return table
end

M.merge = M.extend

M.add = function(table, val)
	table.insert(val)
end

M.remove_one = function(table, target)
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

M.remove_all = function(table, target)
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

M.raw_remove_one = function(table, target)
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

M.raw_remove_all = function(table, target)
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

M.each = function(table, iter, ...)
	table = table or {}
	for k,v in pairs(table) do 
		iter(v, k, ...)
	end
end

M.map = function(table, iter)
	local results = {}
	M.each(table, function(val, key)
			results[#results + 1] = iter(val, key)
		end)
	return results
end

M.reduce = function (table, iter, memo)
	M.each(table, function (val, key)
		memo = iter(val, key, memo)
	end)
	return memo
end

M.find = function (table, iter)
	table = table or {}
	for k,v in pairs(table) do 
		if iter(v, k) then
			return v
		end
	end
	return nil
end

M.filter = function (table, iter)
	local results = {}
	M.each(table, function(val, key)
		if iter(val, key) then 
			results[#results + 1] = val
		end
	end)
	return results
end

M.select = M.filter

M.every = function (table, iter)
	M.each(table, function(val, key)
		if not iter(val, key) then 
			return false
		end
	end)
	return true
end

M.any = function (table, iter)
	table = table or {}
	for k, v in pairs(table) do
		if iter(v, k) then
			return true
		end
	end
	return false
end

M.contains = function (table, target)
	table = table or {}
	for k,v in pairs(table) do
		if v == target then
			return true
		end
	end
	return false
end

M.raw_contains = function (table, target)
	table = table or {}
	for k,v in pairs(table) do
		if rawcompare(v, target) then
			return true
		end
	end
	return false
end

M.max = function (table, iter)
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

M.min = function (table, iter)
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

M.group_by = function (table, iter)
	local results = {}
	table = table or {}
	for k, v in pairs(table) do
		results[iter(v, k)] = v
	end
	return results
end

