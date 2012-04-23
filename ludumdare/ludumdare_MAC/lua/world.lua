world = {
	obj = object2d.new(),
}

world.obj:position(game_options.world_x, game_options.world_y)

world.start_frame = function(elapsed_time)  
	local r, d = player.obj:position()
	local radius = planet.radius
	local x, y = world.obj:position()
	
	world.obj:rotation(-r)
	world.obj:position(x, (-d * 0.5) + game_options.world_v_offset)
	
--	local scale = game_options.world_scale - ((d - radius + 1) * 0.008)
	
	local scale = game_options.world_scale - (((d - radius + 1) * 0.0008) * game_options.world_scale)
	
	world.obj:scale(scale, scale)

	world.obj:update(elapsed_time)
	world.obj:apply_transform()
end

world.end_frame = function(elapsed_time)  
	world.obj:remove_transform()
end
