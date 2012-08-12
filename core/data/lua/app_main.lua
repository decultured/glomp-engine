dofile(LUA_PATH.."util.lua")
dofile("printing")
dofile("json")
dofile("UUID")

function glomp_run_stuff()
	dofile("table_utils")
	dofile("event")
	dofile("description")
	dofile("view")
end

function glomp_load_libs()
	dofile("input_defines")
	dofile("input")
	dofile("window")
end

function glomp_run_tests()
	dofile("model_tests")
	dofile("playground")
end

glomp_run_stuff()
glomp_load_libs()
glomp_run_tests()