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


function glomp_load_libs()
print("#########################")
print("## Reloading Libraries ##")
print("#########################")
print("")

	dofile(LUA_PATH.."input_defines.lua")
	dofile(LUA_PATH.."test_bed.lua")
	dofile(LUA_PATH.."input.lua")
	dofile(LUA_PATH.."window.lua")
	dofile(LUA_PATH.."util.lua")

print("")
print("")
print("")

end

glomp_load_libs()

