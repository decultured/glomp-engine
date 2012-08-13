glOMP.graphics.enable_alpha_blending()

function glomp_libs()
	dofile(LUA_PATH.."util.lua")
	dofile("printing")
	dofile("json")
	dofile("UUID")
end

function glomp_structure()
	dofile("table_utils")
	dofile("event")
	dofile("description")
	dofile("view")
end

function glomp_app()
	dofile("input_defines")
	dofile("input")
	dofile("window")
	dofile("gui/load_gui")
end

function glomp_run_tests()
	dofile("basic_input")
	dofile("model_tests")
	dofile("playground")
end

glomp_libs()
glomp_structure()
glomp_app()

glomp_run_tests()