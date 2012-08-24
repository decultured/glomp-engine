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

function load_module_error(err)
	if not err then
		print("Unknown Error")
		return
	end

	local err = string.gsub(err, "(.-/)", "")
	local pos = string.find(err, ":%s")

	if not pos then
		warning(err)
		return
	end

	local err_text = string.sub(err, 1, pos+1).."\n    "..string.sub(err, pos+2, -1)
	warning(err_text)
end

local builtin_dofile = dofile
function load_module(filename)
	filename = LUA_PATH .. filename .. ".lua"
	-- local printname = string.gsub(filename, "(.-/)", "")
	-- print(printname)
	local f, err = loadfile(filename)
	if not f then
		load_module_error(err)
		return false
	end
	local status, result = pcall(f)
	if not status then
		load_module_error(result)
		return false
	end
	return result
end

glomp_print_queue = glomp_print_queue or {}

local old_print = print
function print(...)
	local out = {}
	local args = {}
	local arg
    local arg_type

	for i = 1, select("#", ...) do
		arg = select(i, ...)
        arg_type = type(arg)
		if not arg then 
			arg = "nil"
        elseif type(arg) == "table" then
		-- elseif type (arg) == "table" then
			-- glomp_printobj(arg)
			-- if arg.tostring then
			-- 	arg = arg.tostring()
			-- else
				arg = "Object:\n\t" .. json.encode(arg) .. "\n"
			-- end
		end

        out[#out + 1] = tostring(arg)
	end

    local out_string = table.concat(out, " ")
    glomp_print_queue[#glomp_print_queue + 1] = out_string
	
	old_print(out_string)
end

local old_error = error
function error(text, level)
	print(text)
    print(debug.traceback())
	old_error(text, level + 1)
end

function warning(...)
	print(...)
    print(debug.traceback())
end

function split(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local t={}
    local pat = "([^"..sep.."]+)"
    for str in string.gmatch(inputstr, pat) do
        t[#t + 1] = str
    end
    return t
end

-- TODO : this is likely slow, copypasta
function hex_to_rgb(hex)
	hex = hex:gsub("#","")
	return tonumber("0x"..hex:sub(1,2)), tonumber("0x"..hex:sub(3,4)), tonumber("0x"..hex:sub(5,6))
end

function rgb_to_hex ( nR, nG, nB )
    local sColor = "#"
    nR = string.format ( "%X", nR )
    sColor = sColor .. ( ( string.len ( nR ) == 1 ) and ( "0" .. nR ) or nR )
    nG = string.format ( "%X", nG )
    sColor = sColor .. ( ( string.len ( nG ) == 1 ) and ( "0" .. nG ) or nG )
    nB = string.format ( "%X", nB )
    sColor = sColor .. ( ( string.len ( nB ) == 1 ) and ( "0" .. nB ) or nB )
    return sColor
end