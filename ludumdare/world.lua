world1_tex = image.new()
world1_tex:load("world1.tga")

world_obj = object2d.new()

world = {
	obj = world_obj,
	globe_offset = -192,
	inside_offset = 512
}

world_obj:set_texture_id(world1_tex:get_id())
world_obj:size(1024, 1024)
world_obj:position(400, -192)

game_input:on("toggle", function () 
	x, y = world_obj:position()
	
	if y == world.globe_offset then
		world_obj:position(x, world.inside_offset)
	else
		world_obj:position(x, world.globe_offset)
	end	

end)

world.update = function(elapsed_time)  
	world_obj:update(elapsed_time)
	world_obj:render()
end

