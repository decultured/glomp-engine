function glomp_printobj(obj)
	print ("\nObject:")
	for key, val in ipairs(obj) do
		print(key, val)
	end

	if (obj.__index) then
		print ("\n__Index:")	
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
function dofile(filename)
	local printname = string.gsub(filename, "(.-/)", "")
	print("## Loading "..printname.."...")
	
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

