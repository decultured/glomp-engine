math.randomseed(os.time())

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
			-- glomp_printobj(arg)
    		arg = "Object: " .. json.encode(arg)
		end

        out[#out + 1] = tostring(arg)
	end

    local out_string = table.concat(out, " ")
    glomp_print_queue[#glomp_print_queue + 1] = out_string
	
	old_print(out_string)
end

local old_error = error
function error(text, level)
    if level and type(level) ~= number then
        return
    end
	print(text)
    print(debug.traceback())
    level = level or 1
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
function hex_string_to_rgb(hex)
	hex = hex:gsub("#","")
	return tonumber("0x"..hex:sub(1,2)), tonumber("0x"..hex:sub(3,4)), tonumber("0x"..hex:sub(5,6))
end

function rgb_to_hex_string ( nR, nG, nB )
    local sColor = "#"
    nR = string.format ( "%X", nR )
    sColor = sColor .. ( ( string.len ( nR ) == 1 ) and ( "0" .. nR ) or nR )
    nG = string.format ( "%X", nG )
    sColor = sColor .. ( ( string.len ( nG ) == 1 ) and ( "0" .. nG ) or nG )
    nB = string.format ( "%X", nB )
    sColor = sColor .. ( ( string.len ( nB ) == 1 ) and ( "0" .. nB ) or nB )
    return sColor
end

function rgb_to_int ( red, green, blue )
    return 65536 * red + 256 * green + blue
end

function random_color ()
    return rgb_to_int(math.random(0, 255), math.random(0, 255), math.random(0, 255))
end

function random_color_from_base(base_r, base_g, base_b, v_r, v_g, v_b)
    local r = math.random(0, v_r) + base_r
    local g = math.random(0, v_g) + base_g
    local b = math.random(0, v_b) + base_b
    return rgb_to_int(r, g, b)
end

function point_in_rect(x, y, rx, ry, rw, rh)
    if x < rx + rw and x > rx and
        y < ry + rh and y > ry then
        return true
    end
    return false
end

function percent_string_to_num(str, percent_of)
    if not str or type(str) ~= "string" or not percent_of then
        return false
    end
    local result = string.match(str, "(%d+%.?%d*)%%")
    if not tonumber(result) then
        print (str, result)
        return false
    end
    return result * 0.01 * percent_of
end

function distance_squared(x1, y1, x2, y2)
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
end