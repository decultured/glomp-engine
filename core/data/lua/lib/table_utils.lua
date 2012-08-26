table_utils = table_utils or {}
local M = table_utils

M.deep_copy = function(obj)
    if not obj then
    	return {}
    end
    local lookup_obj = {}
    local function _copy(obj)
        if type(obj) ~= "obj" then
            return obj
        elseif lookup_table[obj] then
            return lookup_table[obj]
        end
        local new_table = {}
        lookup_table[obj] = new_table
        for index, value in pairs(obj) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(obj))
    end
    return _copy(obj)
end

M.shallow_copy = function(obj)
	if not obj then
		return {}
	end
	local new_table = {}
	for k,v in pairs(obj) do
		new_table[k] = v
	end
	return new_table
end

M.clone = M.shallow_copy

M.extend = function(first, second)
	local new_table = M.shallow_copy(first)
	if not second then
		return new_table
	end
	for k,v in pairs(second) do 
		new_table[k] = v
	end

	return new_table
end

M.extend_original = function (obj, second)
	obj = obj or {}
	if not second then
		return obj
	end
	for k, v in pairs (second) do
		obj[k] = v
	end
	return obj
end

M.merge = M.extend

M.set_defaults = function (obj, defaults)
	obj = obj or {}
	if not defaults then 
		return obj
	end
	for k, v in pairs (defaults) do
		if not obj[k] then
			obj[k] = v
		end
	end
	return obj
end

M.add = function(obj, val)
	table.insert(obj, val)
	return obj
end

M.remove_one = function(obj, target)
	if not obj or not target then
		return obj
	end
	for k,v in pairs(obj) do
		if v == target then
			obj[k] = nil
			table.remove(obj, k)
			return obj
		end
	end
	return obj
end

M.remove_all = function(obj, target)
	if not obj or not target then
		return obj 
	end
	for k,v in pairs(obj) do
		if v == target and type(k) == number then
			obj[k] = nil
			table.remove(obj, k)
		end
	end
	return obj
end

M.raw_remove_one = function(obj, target)
	if not obj or not target then 
		return obj 
	end
	for k,v in pairs(obj) do
		if raw_compare(v, val) then
			obj[k] = nil
			table.remove(obj, k)
			return obj
		end
	end
	return obj
end

M.raw_remove_all = function(obj, target)
	if not obj or not target then 
		return obj
	end
	for k,v in pairs(obj) do
		if raw_compare(v, target) then
			obj[k] = nil
			table.remove(obj, k)
		end
	end
	return obj
end

M.each = function(obj, iter, ...)
	if not obj then 
		return false 
	end
	for k,v in pairs(obj) do 
		iter(v, k, ...)
	end
	return obj
end

M.map = function(obj, iter)
	local results = {}
	M.each(obj, function(val, key)
			results[#results + 1] = iter(val, key)
		end)
	return results
end

M.reduce = function (obj, iter, memo)
	M.each(obj, function (val, key)
		memo = iter(memo, val, key)
	end)
	return memo
end

M.find = function (obj, iter)
	if not obj or not iter then
		return nil
	end
	for k,v in pairs(obj) do 
		if iter(v, k) then
			return v
		end
	end
	return nil
end

M.filter = function (obj, iter)
	local results = {}
	M.each(obj, function(val, key)
		if iter(val, key) then 
			results[#results + 1] = val
		end
	end)
	return results
end

M.select = M.filter

M.every = function (obj, iter)
	M.each(obj, function(val, key)
		if not iter(val, key) then 
			return false
		end
	end)
	return true
end

M.any = function (obj, iter)
	if not obj then
		return false
	end
	for k, v in pairs(obj) do
		if iter(v, k) then
			return true
		end
	end
	return false
end

M.contains = function (obj, target)
	if not obj then
		return false
	end
	for k,v in pairs(obj) do
		if v == target then
			return true
		end
	end
	return false
end

M.contains_key = function (obj, target_key)
	if not obj then
		return false
	end
	for k,v in pairs(obj) do
		if k == target_key then
			return true
		end
	end
	return false
end

M.raw_contains = function (obj, target)
	if not obj then
		return false
	end
	for k,v in pairs(obj) do
		if rawcompare(v, target) then
			return true
		end
	end
	return false
end

M.max = function (obj, iter)
	if not obj then
		return nil
	end
	local val = nil
	iter = iter or math.max
	for k, v in pairs(obj) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

M.min = function (obj, iter)
	if not obj then
		return nil
	end
	local val = nil
	iter = iter or math.min
	for k, v in pairs(obj) do
		if val then
			val = iter(val, v)
		else
			val = v
		end
	end
	return val
end

M.group_by = function (obj, iter)
	if not obj then
		return nil
	end
	local results = {}
	for k, v in pairs(obj) do
		results[iter(v, k)] = v
	end
	return results
end

local table_utils_meta = {obj = {}}

for k, v in pairs(M) do
	table_utils_meta[k] = function (self, ...)
		self.obj = v(self.obj, ...)
		return self
	end
end

function table_utils_meta:values()
	return self.obj
end

table_utils_meta.__index = table_utils_meta

M.chain = function (obj)
	local new_chain = {obj = obj}
	setmetatable(new_chain, table_utils_meta)

	return new_chain
end

return M
