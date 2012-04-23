game_object_settings =  {
	name = "game object",
	x = 0,
	y = 600,
	width = 64,
	height = 64,
	rotation = 0,
	center_x = 0,
	center_y = 0,
	tx = 0,
	ty = 0,
	tw = 0,
	tz = 0,
	r = 1,
	g = 1,
	b = 1,
	a = 1,
	texture_id = 0,
	polar = true,	
	new = function(self, base)
		local new_obj = base or {}
		setmetatable(new_obj, self)
		self.__index = self
		return new_obj
	end
}

game_object = {		
	name = "game object",
	drawable = true,

	_update_callbacks = {},
	_children = {},

	settings = game_object_settings:new(),
	translate = function(self, x, y)
		return self.sprite:translate(x,y)
	end,
	position = function(self, x, y)
		return self.sprite:position(x,y)
	end,

	new = function (self, settings, base)
		base = base or {}
		local new_obj = base
		setmetatable(new_obj, self)
		self.__index = self

		new_obj.settings = self.settings:new(settings) or {}
		local settings = new_obj.settings

		new_obj._update_callbacks = {}
		new_obj.name = settings.name
		new_obj.sprite = object2d.new()
		new_obj.sprite:rotation(settings.rotation)
		new_obj.sprite:center(settings.center_x, settings.center_y)
		new_obj.sprite:set_texture_id(settings.texture_id)
		new_obj.sprite:color(settings.r, settings.g, settings.b, settings.a)
		new_obj.sprite:texture_coords(settings.tx, settings.ty, settings.tw, settings.th)
		new_obj.sprite:make_polar(settings.polar)
		new_obj.sprite:size(settings.width, settings.height)
		new_obj.sprite:position(settings.x, settings.y)
	
		return new_obj
	end,

	on_update = function(self, callback)
		self._update_callbacks[#self._update_callbacks + 1] = callback
	end,

	update = function (self, seconds)
		local spr = self.sprite
		spr:update(seconds)

		local callbacks = self._update_callbacks
		for k, v in ipairs(callbacks) do
			v(self, seconds)
		end
		
		callbacks = self.__index._update_callbacks
		for k, v in ipairs(callbacks) do
			v(self, seconds)
		end
		
		spr:apply_transform()
			if self.drawable then
				spr:draw()
			end
		spr:remove_transform()
	end
}