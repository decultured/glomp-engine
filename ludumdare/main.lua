dofile("input_defines.lua")
dofile("game_config.lua")
dofile("game_loop.lua")
dofile("world.lua")
dofile("player.lua")

bind_actions(game_bindings)

game_loop(function (seconds) 
	world.update(seconds)
	player.update(seconds)
end)