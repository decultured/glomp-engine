game_object_settings =  {
	x = 150,
	y = 250,
	width = 64,
	height = 64,
	rotation = 0,
	center_x = 0,
	center_y = 0,
	tx = 0,
	ty = 0,
	tw = 0,
	tz = 0,
	texture_id = 0
}

game_object = {		
	children = {},
	translate = function(x, y)
		return self.sprite:translate(x,y)
	end,
	new = function (self, settings, base)
		settings = settings or {}
		setmetatable(settings, game_object_settings)

		new_obj = base or {}
		setmetatable(new_obj, self)
		self.__index = self

		new_obj.sprite = object2d.new()

		print (settings.x, settings.texture_id)
	
		new_obj.sprite:position(settings.x, settings.y)
		new_obj.sprite:rotation(settings.rotation)
		new_obj.sprite:center(settings.center_x, settings.center_y)
		new_obj.sprite:set_texture_id(settings.texture_id)
		new_obj.sprite:texture_coords(settings.tx, settings.ty, settings.tw, settings.th)
		new_obj.sprite:make_polar(settings.polar)
		new_obj.sprite:size(settings.width, settings.height)
	
		return new_obj
	end,

	update = function (self, seconds)
		self.sprite:update(seconds)
		self.sprite:apply_transform()
			self.sprite:draw()
		self.sprite:remove_transform()
	end
}