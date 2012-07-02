builtin_dofile = dofile
function dofile(filename)
	local f, err = loadfile(filename)
	if not f then
		err = string.gsub(err, "(.-/)", "")
		pos = string.find(err, ":%s")
		err_one = string.sub(err, 1, pos+1)
		err_two = "    "..string.sub(err, pos+2, -1)
		print(err_one)
		print(err_two)
		return
	end
	f()
end


function glomp_load_libs()
	dofile(LUA_PATH.."input_defines.lua")
	dofile(LUA_PATH.."test_bed.lua")
	dofile(LUA_PATH.."input.lua")
	dofile(LUA_PATH.."window.lua")
	dofile(LUA_PATH.."util.lua")
end

glomp_load_libs()

