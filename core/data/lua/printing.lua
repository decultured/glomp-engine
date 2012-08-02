-- Testing the app stuffs

function process_event(event)
	if event.type == "label" and event.action == "update" then
		print_event(event.name, event.data)
	end
end

function print_event(name, data)
	print_more(name, data.text, data.x, data.y)
end

-- local old_error = error
-- error = function(...)
-- 	print(...)
-- 	old_error()
-- end

function glomp_printobj(obj, indent)
	indent = indent or ""
	print (indent .. "Object:")
	indent = indent .. "\t"
	for key, val in pairs(obj) do
		if type(val) == "table" then
			print(indent .. key, "-", "Object:")
			glomp_printobj(val, indent)
		else
			print(indent .. key, "-", val)
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

