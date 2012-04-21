planet_tex = image.new()
planet_tex:load("world2.tga")

planet = {
	obj = object2d.new(),
	radius = 448
}

planet_time = 0.1;

planet.obj:set_texture_id(planet_tex:get_id())
planet.obj:make_polar(true)
planet.obj:size(1024, 1024)
planet.obj:position(0, 0)

planet.update = function(elapsed_time)  
	planet.obj:update(elapsed_time)
	planet.obj:render()
end

