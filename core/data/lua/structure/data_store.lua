glomp = glomp or {}
glomp.data_store = glomp.data_store or {}

local M = glomp.data_store

function M:get(key)
	return self.store[key]
end

function M:set(key, value)
	self.store[key] = value
end

function M:has(key)
	return self.store[key] ~= nil
end

M.store = {}