player_bullet_image = image.new()
player_bullet_image:load("bullet.tga")

print(player_bullet_image:get_id())

background_object = game_object:new({
	texture_id = player_bullet_image:get_id()
})