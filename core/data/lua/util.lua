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

local old_print = print
function print(...)
	local out = "\n"
	local args = {}
	local arg

	for i = 1, select("#",...) do
		arg = select(i, ...)
		if not arg then 
			arg = "nil"
		elseif type (arg) == "table" then
			if arg.tostring then
				arg = arg.tostring()
			else
				arg = json.encode(arg)
			end
		end
		out = string.format("%s %s", out, tostring(arg))
	end

	glomp_print_queue[#glomp_print_queue + 1] = out
	
	old_print(...)
end

local old_error = error
function error(...)
	print(...)
	old_error(...)
end

function warning(...)
	print(...)
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