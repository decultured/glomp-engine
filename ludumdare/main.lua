dofile("game_loop.lua")
dofile("world.lua")
dofile("player.lua")

game_loop(function (seconds) 
	world.update(seconds)
	player.update(seconds)
end)