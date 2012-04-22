player_image = image.new()
player_image:load("player.tga")

zap = sound.new()
zap:load_wav("Sound.wav")

player = {
	obj = object2d.new(),
	lwheel = object2d.new(),
	rwheel = object2d.new(),
	rot_speed = 30,
	jump_speed = 400,
	wheel_speed = 400,
	velocity_d = 0,
	velocity_r = 0,
	accel_g = 900
}

player.obj:set_texture_id(player_image:get_id())
player.obj:texture_coords(0, 0.5, 1.0, 0.5)
player.obj:make_polar(true)
player.obj:position(45, planet.radius)
player.obj:size(128, 64)
player.obj:center(0, -32)

player.lwheel:set_texture_id(player_image:get_id())
player.lwheel:texture_coords(0, 0, 0.34375, 0.34375)
player.lwheel:position(-38, -22)
player.lwheel:size(44, 44)

player.rwheel:set_texture_id(player_image:get_id())
player.rwheel:texture_coords(0, 0, 0.34375, 0.34375)
player.rwheel:position(38, -22)
player.rwheel:size(44, 44)

game_input:on("right", function() 
	player.obj:translate(-game_frame_time * player.rot_speed, 0)
	player.lwheel:rotate(-game_frame_time * player.wheel_speed, 0)
	player.rwheel:rotate(-game_frame_time * player.wheel_speed, 0)
end)

game_input:on("left", function()
	player.obj:translate(game_frame_time * player.rot_speed, 0)
	player.lwheel:rotate(game_frame_time * player.wheel_speed, 0)
	player.rwheel:rotate(game_frame_time * player.wheel_speed, 0)
end)

game_input:on("jump", function()
	player.velocity_d = player.jump_speed
end)

player.update = function(elapsed_time)
	player.obj:update(elapsed_time)

	player.velocity_d = player.velocity_d - (elapsed_time * player.accel_g)
	player.obj:translate(0, player.velocity_d * elapsed_time)
	r, d = player.obj:position()

	if d < planet.radius then
		player.velocity_d = 0.0
		player.obj:position(r, planet.radius)
	end
		
	player.obj:apply_transform()
	player.obj:draw()
	player.lwheel:render()
	player.rwheel:render()
	player.obj:remove_transform()
end
