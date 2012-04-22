player_bullet_image = image.new()
player_bullet_image:load("bullet.tga")

background_object = game_object:new({
	texture_id = meteor_image:get_id(),
	x = 0,
	y = 0,
	width = 16,
	height = 16,
	rotation = 0,
	center_x = 0,
	center_y = 0,
}