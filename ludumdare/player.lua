player_image = image.new()
player_image:load("player.tga")

zap = sound.new()
zap:load_wav("Sound.wav")

player = {
	obj = object2d.new(),
}
player.obj:set_texture_id(player_image:get_id())

player.update = function(elapsed_time)
	player.obj:update(elapsed_time)
	player.obj:render()
end
