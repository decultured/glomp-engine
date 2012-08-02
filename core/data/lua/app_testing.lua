-- Testing the app stuffs

glomp_print_queue = glomp_print_queue or {}

print_message_test = print_message_test or {
	action = "update",
	name = "game.print",
	type = "label",
	data = {
		text = "",
		x = 10,
		y = 380
	}
}

function print(...)
	local out = ""
	local arg = {...}

	for k,v in pairs(arg) do
		if type (v) == "table" then
			if v.tostring then
				arg[k] = v.tostring(v)
			else
				arg[k] = tostring(v)
			end

			-- else

			-- if v then
			-- 	arg[k] = tostring(v)	
			-- else
				-- arg[k] = json.encode(v)
			-- end
		end
	end

	out = table.concat(arg, " ") .. "\n"

	glomp_print_queue[#glomp_print_queue + 1] = out
	print_message_test.data.text = print_message_test.data.text .. out
	print_message_test.data.y = print_message_test.data.y - 18
	process_event(print_message_test)
end

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

function print_error(err)
	local err = string.gsub(err, "(.-/)", "")
	local pos = string.find(err, ":%s")

	if not pos then
		print (err)
		return
	end

	local err_one = string.sub(err, 1, pos+1)
	local err_two = "    "..string.sub(err, pos+2, -1)
	print(err_one)
	print(err_two)
end
