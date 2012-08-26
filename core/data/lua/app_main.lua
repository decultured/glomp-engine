dofile(LUA_PATH.."system/util.lua")

function glomp_libs()
	load_module("system/printing")
	load_module("lib/json")
	load_module("lib/UUID")
	load_module("lib/table_utils")
end

function glomp_structure()
	load_module("structure/data_store")
	load_module("structure/event_pump")
	load_module("structure/definition")
	load_module("structure/description")
	load_module("structure/collection")
	load_module("structure/resource")
end

function glomp_app()
	load_module("system/input_defines")
	load_module("input")
	load_module("window")
end

function glomp_run_game()
	load_module("game/load")
end

glomp_libs()
glomp_structure()
glomp_app()

glomp_run_game()