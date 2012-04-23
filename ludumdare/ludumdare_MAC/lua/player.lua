player = {
	obj = object2d.new(),
	lwheel = object2d.new(),
	rwheel = object2d.new(),
	rot_speed = game_options.player_speed,
	jump_speed = 600,
	wheel_speed = 400,
	velocity_d = 0,
	velocity_r = 0,
	accel_g = game_options.gravity,
	life = game_options.player_life,
	max_distance = 200
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
	if state ~= "game" then
		return
	end
	sounds.motor:play_loop();
	player.obj:translate(-game_frame_time * player.rot_speed, 0)
	player.lwheel:rotate(-game_frame_time * player.wheel_speed, 0)
	player.rwheel:rotate(-game_frame_time * player.wheel_speed, 0)
end)

game_input:on("right_stop", function() 
	sounds.motor:stop();
end)

game_input:on("left_stop", function() 
	sounds.motor:stop();
end)

game_input:on("left", function()
	if state ~= "game" then
		return
	end
	sounds.motor:play_loop();
	player.obj:translate(game_frame_time * player.rot_speed, 0)
	player.lwheel:rotate(game_frame_time * player.wheel_speed, 0)
	player.rwheel:rotate(game_frame_time * player.wheel_speed, 0)
end)

game_input:on("jump", function()
	if state ~= "game" then
		return
	end
	local r, d = player.obj:position()
	if player.max_distance > d - planet.radius then
		player.velocity_d = player.jump_speed
	end
end)

last_fired = -1000
fire_rate = 0.1
fire_elapsed = 100
game_input:on("fire", function()
	if state ~= "game" then
		return
	end
	fire_elapsed = game_frame_time + fire_elapsed
	if fire_elapsed < fire_rate then
		return
	else
		fire_elapsed = 0
	end

--	zap:play()
	sounds.bew:play()
	
	local x_pos, y_pos = player.obj:position()

	local new_bullet = bullet_obj:new({
		x = x_pos,
		y = y_pos
	},{
			
	})
	
	local last = 0
	for k, v in ipairs(bullets) do
		if not v then
			bullets[k] = new_bullet
			last = -1
			break
		end
		last = k
	end
	if last > -1 then
		bullets[last +1] = new_bullet
	end
end)

player.update = function(elapsed_time)
	player.obj:update(elapsed_time)

	player.velocity_d = player.velocity_d - (elapsed_time * player.accel_g)
	player.obj:translate(0, player.velocity_d * elapsed_time)
	r, d = player.obj:position()

	if d < planet.radius and player.velocity_d < 0 then
		player.velocity_d = - player.velocity_d * 0.5
		player.obj:position(r, planet.radius)
	end
		
	player.obj:apply_transform()
	player.obj:draw()
	player.lwheel:render()
	player.rwheel:render()
	player.obj:remove_transform()
end

function player:collides_with(two_rad, two_d, two_size)
	local two_width = two_size * 0.5
	local two_height = two_size * 0.5
	local one_rad, one_d = self.obj:position()
	local one_width, one_height = self.obj:size()
	one_width = one_width * 0.5
	one_height = one_height * 0.5


	local coll = false

	if two_d - two_height > one_d + one_height or two_d + two_height < one_d - one_height then
		return false
	end

	-- testee angle - testee angular width
	local one_l = (one_rad - 2)
	-- testee angle - testee angular width
	local one_r = (one_rad + 2)
	-- testing.getRotation() + testingAngle
	local two_l = (two_rad - 1)
	-- testing.getRotation() - testingAngle
	local two_r = (two_rad + 1)
	

	if one_l < two_l and one_l > two_r then
		coll = true
	elseif one_r > two_r and one_r < two_l then
		coll = true

	elseif one_l < two_r and one_r > two_l then
		coll = true
	elseif one_l > two_r and one_r < two_l then
		coll = true
	end


	return coll
end

