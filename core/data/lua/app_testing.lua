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
			if v then
				arg[k] = tostring(v)	
			else
				arg[k] = json.encode(v)
			end
		end
	end

	out = table.concat(arg, " ") .. "\n"
	-- for i,v in ipairs(arg) do
	-- 	if i ~= 0 then
 --        	out = out .. ", " .. tostring(v)
 --        else
 --        	out = tostring(v)
 --        end
 --    end
 --    out = out .. "\n"


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

-- local message_test = {
-- 	action = "update",
-- 	name = "game.framerate",
-- 	type = "label",
-- 	data = {
-- 		text = "This is my textsss",
-- 		x = 10,
-- 		y = 170
-- 	}
-- }

-- local json_output = json.encode(message_test)

-- local binary_output = marshal.encode(message_test)

-- print_more("message_test", json_output, 10, 80)

-- print_more("binary_test", binary_output, 10, 110)

-- local out = marshal.decode(binary_output)

-- process_event(out)

-- local second_out = json.encode(out)

-- print_more("decode_test", second_out, 10, 140)

-- print("Console Goes Here")

-- local a = 5
-- local b = {5}

-- if type(a) == "table" then
-- 	print(pairs(a))
-- end


