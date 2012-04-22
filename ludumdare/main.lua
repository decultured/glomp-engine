dofile("util.lua")
dofile("game_object.lua")
dofile("input_defines.lua")
dofile("game_config.lua")
dofile("game_loop.lua")
dofile("world.lua")
dofile("planet.lua")
dofile("player.lua")
dofile("background_obj.lua")


game_window:set_clear_color(0.0, 0.0, 0.0)
bind_actions(game_bindings)

meteor = background_object:new({name = "meteor", x = 45, y = 600})
meteor2 = background_object:new({name = "meteor2", x = 90, y = 900})

stars = {}
local num_stars = 2000
for i=1,num_stars do
	local star = star_object:new({
		name = "star",
		y = math.random(0, 1000) + planet.radius,
		x = math.random() * 360.0,
		tx = math.random(0, 4) * 0.25,
		ty = math.random(0, 4) * 0.25,
		a = math.random() * 0.5 + 0.4
	},
	{
		rotation_speed = math.random(0, 16) - 8
	})
	stars[i] = star
end

for i=1,num_stars do
	local star = star_object:new({
		name = "star",
		y = math.random(0, 1000) + planet.radius,
		x = math.random() * 360.0,
		tx = math.random(0, 4) * 0.25,
		ty = math.random(0, 4) * 0.25,
		width = 16,
		height = 16
	},
	{
		rotation_speed = math.random(0, 16) - 8
	})
	stars[i + 1000] = star
end

elapsed_frame_time = 0
frames = 0

game_loop(function (seconds) 
	world.start_frame(seconds)
		for k, v in pairs(stars) do
			stars[k]:update(seconds)
		end

		planet.update(seconds)
		player.update(seconds)
		meteor:update(seconds)
		meteor2:update(seconds)

	world.end_frame(seconds)
end)