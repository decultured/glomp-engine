dofile(LUA_PATH.."util.lua")
dofile("printing")
dofile("json")

function glomp_run_current()
	dofile("lunatest")
	dofile("underscore")
	dofile("model")
	dofile("model_tests")
end

function glomp_load_libs()
	dofile("input_defines")
	dofile("input")
	dofile("window")
end

glomp_load_libs()
glomp_run_current()