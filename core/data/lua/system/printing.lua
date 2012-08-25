function glomp_printobj(obj, indent)
	indent = indent or ""
	indent = indent .. "\t"

	if string.len(indent) > 20 then
		error("Too deep!")
		return
	end
	for key, val in pairs(obj) do
		if type(val) == "table" then
			print(indent .. tostring(key), "-", "Object:")
			glomp_printobj(val, indent)
		elseif type(val) == "function" then
			print(indent .. tostring(key), "-", tostring(val))
		else
			print(indent .. tostring(key), "-", tostring(val))
		end
	end

	if obj.__index and obj.__index ~= obj then
		print (indent .. "__index:", tostring(obj.__index), tostring(obj))
		-- glomp_printobj(obj.__index, indent)
		-- for key, val in ipairs(obj.__index) do
		-- 	print(key, val)
		-- end
	end
end

function glomp_sprintobj(obj)
	local str = "Object: "

	-- object = 
	-- for key, val in ipairs(obj) do
	-- 	str .. key .. ", " .. val .. "\n"
	-- end

	-- if (obj.__index) then
	-- 	print ("\n__Index:")	
	-- 	for key, val in ipairs(obj.__index) do
	-- 		print(key, val)
	-- 	end
	-- end
end

