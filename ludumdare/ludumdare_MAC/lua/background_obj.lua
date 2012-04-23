background_object = game_object:new({
	texture_id = meteor_image:get_id(),
	tx = 0.0,
	ty = 0.5,
	tw = 0.5,
	th = 0.5,
	width = 128,
	height = 128
})

background_object:on_update(function (self, seconds)
	self.sprite:rotate(seconds*90)
end)

star_object = game_object:new({
	texture_id = stars_image:get_id(),
	tx = 0.0,
	ty = 0.0,
	tw = 0.25,
	th = 0.25,
	width = 8,
	height = 8,
	
},
{
	rotation_speed = -2	
})

star_object:on_update(function (self, seconds)
	self.sprite:rotate(seconds*self.rotation_speed)
end)
