player_bullet_image = image.new()
player_bullet_image:load("bullet.tga")

player_bullet =  {
	x = 150,
	y = 250,
	width = 64,
	height = 64,
	rotation = 0,
	center_x = 0,
	center_y = 0,
	new = function (self, obj)
		obj = obj or {}
		setmetatable(obj, self)
		self.__index = self

		obj.sprite = new object2d()

		obj.sprite:position(obj.x, obj.y)
		obj.sprite:rotation(obj.rotation)
		obj.sprite:center(obj.center)

		return obj
	end	
}