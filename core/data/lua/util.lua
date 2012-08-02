-- break os.exit
os.exit = function (...)
	-- error("Exit not allowed, params: (".. ... .. ")")
end

-- This runs a script within a specified environment
-- this prevents it from polluting the global namespace
function run(scriptfile)
    local env = setmetatable({}, {__index=_G})
    assert(pcall(setfenv(assert(loadfile(scriptfile)), env)))
    setmetatable(env, nil)
    return env
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

local builtin_dofile = dofile
dofile = function(filename)
	filename = LUA_PATH .. filename .. ".lua"
	-- local printname = string.gsub(filename, "(.-/)", "")
	-- print(printname)
	local f, err = loadfile(filename)
	if not f then
		print_error(err)
		return
	end
	local status, err = pcall(f)
	if not status then
		print_error(err)
	end
end

glomp_print_queue = glomp_print_queue or {}

print_message_test = print_message_test or {
	action = "update",
	name = "game.print",
	type = "label",
	data = {
		text = "",
		x = 10,
		y = 580
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
				arg[k] = json.encode(v)
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
	
	if process_event then
		process_event(print_message_test)
	end
end
