dofile(LUA_PATH.."util.lua")

print ("investigate thread safety -- we be crashing ")

glomp_update_count = 0
function _glomp_update()
	-- print_more("worker_update.count", "Updates: " .. glomp_update_count, 50, 70)
	glomp_update_count = glomp_update_count + 1
end

function glomp_load_libs()
	dofile(LUA_PATH.."input_defines.lua")
	dofile(LUA_PATH.."model.lua")
	dofile(LUA_PATH.."model_tests.lua")
end

function glomp_run_current()
	dofile(LUA_PATH.."model.lua")
	dofile(LUA_PATH.."model_tests.lua")
end


glomp_load_libs()
