dofile(LUA_PATH.."util.lua")
dofile("printing")
dofile("json")

function glomp_run_stuff()
	dofile("underscore")
	dofile("description")
	dofile("model_tests")
end

function glomp_load_libs()
	dofile("input_defines")
	dofile("input")
	dofile("window")
end

glomp_run_stuff()
glomp_load_libs()
