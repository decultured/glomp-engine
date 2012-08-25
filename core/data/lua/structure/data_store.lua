data_store = data_store or {}

local M = data_store

M.store = {}
M.builders = {}

function M:workon(base, name)
    local base_store = self.store[base] or {} 
    local record = base_store[name]

    if not record then
        record = M:create(base, name)
    end

    return record
end

function M:fetch(base, name)
    local base_store = self.store[base] or {} 
    return base_store[name]
end

function M:create(base, name, new_record)
    if not name then
        name = UUID()
    end

    if not new_record then
        new_record = self:build(base)
        if not new_record then
            return false
        end
    end

    if self:has(base, name) then
        error("Record already exists in store: " .. base .. " : " .. name, 2)
        return false
    end

    self.store[base] = self.store[base] or self:create_table(base)
    self.store[base][name] = new_record

    return new_record
end

function M:create_table(name)
    -- TODO : weak references!
    return {}
end

function M:has(base, name)
	local base_store = self.store[base] or {}
    return base_store[name] ~= nil
end

function M:add_builder(base, callback)
    if self.builders[base] then
        error("Data store already has a builder for " .. base, 2)
        return false
    end

    self.builders[base] = callback     
end

function M:build(base)
    local builder = self.builders[base]
    if not builder then
        error("No builder for: " .. base, 2)
        return false
    end
end

local imports = {"each", "map", "reduce", "find", "filter", "select", "every", "any", "contains", "raw_contains", "max", "min", "group_by"}

for k, v in pairs(imports) do
    M[v] = function (self, base, ...)
        local base_store = self.store[base] or {}
        return table_utils[v](base_store, ...)
    end
end


return M