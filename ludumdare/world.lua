world1_tex = image.new()
world1_tex:load("world1.tga")

world = {obj = world_obj}

world_obj = object2d.new()
world_obj:set_texture_id(world1_tex:get_id())
world_obj:size(1024, 1024)
world_obj:position(400, -200)

world.update = function(elapsed_time)  
	world_obj:rotate(elapsed_time * 15)
	world_obj:update(elapsed_time)
	world_obj:render()
end

