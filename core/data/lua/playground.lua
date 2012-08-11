local snd = sound.new("assets/know.mp3", true)
local fnt = font.new("assets/fonts/Cousine-Regular.ttf", 30, true, false, true, 0.9, 100)

local playground = Description.new({
		offset = 0,
		speed = 1,
		pan = 0
	})

playground:on("speed", function(data)
	snd:set_speed(data)
end)

playground:on("pan", function(data)
	snd:set_pan(data)
end)
		
local _keys = glomp.keyboard

_keys:when_equals("A", function() 
		snd:play()
		snd:set_position(playground:get("offset"))
end, 1)

_keys:when_equals("S", function() 
		playground:set("offset", snd:get_position())
		snd:stop()
end, 1)

_keys:when_greater_than("UP", function() 
	playground:add_to("speed", 0.02)
end, 0)

_keys:when_greater_than("DOWN", function() 
	playground:add_to("speed", -0.02)
end, 0)

_keys:when_greater_than("LEFT", function()
	playground:add_to("pan", -0.02)
end, 0)

_keys:when_greater_than("RIGHT", function()
	playground:add_to("pan", 0.02)
end, 0)

_keys:when_greater_than("R", function()
    glomp_run_tests()
end, 0)

_keys:when_greater_than("U", function()
   	print("UUID: "..UUID())
end, 0)

local _is_fullscreen = false

_keys:when_equals("F", function()
   	_is_fullscreen = not _is_fullscreen
   	window.set_fullscreen(_is_fullscreen)
end, 0)

_keys:when_greater_than("Q", function()
    __glomp_terminate()
end, 0)

_keys:when_greater_than("I", function()
    dofile("input")
end, 0)

_keys:when_greater_than("SPACE", function()
    glomp_load_libs()
    glomp_run_stuff()
    glomp_run_tests()
end, 0)

_keys:when_greater_than("O", function()
    system.save_screen("/test.png")
end, 0)

glomp.time:on("frame_time", function (frames, g_time)
	-- TODO : this is *massively* inefficient
	print_more("update.count", "Updates: " .. g_time:get("update_count"), 700, 40)
	print_more("update.time", "Elapsed: " .. g_time:get("frame_time"), 700, 60)
	print_more("update.time_avg", "Average: " .. g_time:get("total_time") / g_time:get("update_count"), 700, 80)
	print_more("update.fps", "FPS: " .. g_time:get("update_count") / g_time:get("total_time"), 700, 100)
	print_more("update.total", "Total: " .. g_time:get("total_time"), 700, 120)
end)

glomp.mouse:on("changed", function(g_mouse)
	print_more("mouse.moved", "<=", g_mouse:get("x"), g_mouse:get("y"));	
end)

print(glOMP.directory.list("/"))