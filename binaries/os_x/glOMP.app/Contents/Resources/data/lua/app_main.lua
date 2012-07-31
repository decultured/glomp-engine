
dofile(LUA_PATH.."json.lua")
dofile(LUA_PATH.."util.lua")

print ("investigate thread safety -- we be crashing ")


function glomp_load_libs()
	dofile(LUA_PATH.."input_defines.lua")
	dofile(LUA_PATH.."input.lua")
	dofile(LUA_PATH.."window.lua")
	dofile(LUA_PATH.."model.lua")
	dofile(LUA_PATH.."model_tests.lua")
end

function glomp_run_current()
	dofile(LUA_PATH.."model.lua")
	dofile(LUA_PATH.."model_tests.lua")
	dofile(LUA_PATH.."app_testing.lua")
end


glomp_load_libs()
