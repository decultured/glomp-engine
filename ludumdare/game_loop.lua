game_window = window.new()
game_window:init(800, 600, true)
game_time = timer.new()
game_input = input.new()
game_audio = audio.new()

active = true

function bind_actions(actions)
	for idx, row in ipairs(actions) do	
		game_input:bind(row[1], row[2], row[3])
	end
end

game_input:bind("quit", "key_down", keyboard.Q)
game_input:on("quit", function () 
	active = false
end)

game_input:on("fire", function ()
	zap:play()
	player:update(1.0)
end)

game_window:start_2d(800, 600, 0, 0)

local elapsed_time = 1.0
function game_loop(callback)
	frames = 0
	
	while active do
		elapsed_time = game_time:elapsed()
		if (elapsed_time > 0.2) then
			elapsed_time = 0.2
		end
		game_time:reset()
		game_window:update()
		game_input:update()
		callback(elapsed_time)
	end
	return frames
end
