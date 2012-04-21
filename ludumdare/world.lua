world = {
	obj = object2d.new(),
	v_offset = game_options.screen_width * 0.1
}

world.obj:position(game_options.screen_width * 0.4, -75)

world.start_frame = function(elapsed_time)  
	local r, d = player.obj:position()
	local x, y = world.obj:position()
	
	world.obj:rotation(-r)
	world.obj:position(x, (-d * 0.7) + world.v_offset)

	world.obj:update(elapsed_time)
	world.obj:apply_transform()
end

world.end_frame = function(elapsed_time)  
	world.obj:remove_transform()
end
