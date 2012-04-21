
win = window.new()
win:init(800, 600, true)

active = true

game_time = timer.new()
game_input = input.new()
game_audio = audio.new()
player = object2d.new()

bush = image.new()
bush:load("test.tga")
player:set_texture_id(bush:get_id())

zap = sound.new()
zap:load_wav("Sound.wav")


game_input:bind("color_change", 65)
game_input:on("color_change", function () 
	win:set_clear_color(random_color())
end)

game_input:bind("quit", 81)
game_input:on("quit", function () 
	active = false
end)

game_input:bind("fire", 90)
game_input:on("fire", function ()
	zap:play()
	player:update(1.0)
end)

win:start_2d(800, 600, 0, 0)

local elapsed_time = 1.0
function game_loop()
	frames = 0
	
	while active do
		elapsed_time = game_time:elapsed()
		if (elapsed_time > 0.2) then
			elapsed_time = 0.2
		end
		game_time:reset()

		win:update()
		game_input:update()
		player:update(elapsed_time)
		player:render()
	end
	return frames
end
