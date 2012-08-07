snd = sound.new("assets/know.mp3", true)
fnt = font.new("assets/fonts/Cousine-Regular.ttf", 30, true, false, true, 0.9, 100)

local playground = Description.new({
		offset = 0,
		speed = 1,
		pan = 0
	})

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

playground:on("speed", function(data)
	snd:set_speed(data)
end)

playground:on("pan", function(data)
	snd:set_pan(data)
end)
		
_keys:when_greater_than("R", function()
    glomp_run_tests()
end, 0)

_keys:when_greater_than("U", function()
   	print("updates: "..glomp_update_count)
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
    system.save_screen("~/test")
end, 0)
