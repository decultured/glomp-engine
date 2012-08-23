function glomp_printobj(obj, indent)
	indent = indent or ""
	indent = indent .. "\t"
	for key, val in pairs(obj) do
		if type(val) == "table" then
			print(indent .. key, "-", "Object:")
			glomp_printobj(val, indent)
		elseif type(val) == "function" then
			print(indent .. tostring(key), "-", "function")
		else
			print(indent .. tostring(key), "-", tostring(val))
		end
	end

	if (obj.__index) then
		print ("__Index:")	
		for key, val in ipairs(obj.__index) do
			print(key, val)
		end
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

