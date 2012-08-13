local _g_keys = glOMP.Description:load("glOMP_keyboard")
local _snd = glOMP.sound.load("assets/know.mp3", true)

local playground = glOMP.Description:load({
		offset = 0,
		speed = 1,
		pan = 0
	})

playground:on("speed", function(data)
	_snd:set_speed(data)
end)

playground:on("pan", function(data)
	_snd:set_pan(data)
end)
		
_g_keys:when_equals("A", function() 
		_snd:play()
		_snd:set_position(playground:get("offset"))
end, 1)

_g_keys:when_equals("S", function() 
		playground:set("offset", _snd:get_position())
		_snd:stop()
end, 1)

_g_keys:when_greater_than("UP", function() 
	playground:add_to("speed", 0.02)
end, 0)

_g_keys:when_greater_than("DOWN", function() 
	playground:add_to("speed", -0.02)
end, 0)

_g_keys:when_greater_than("LEFT", function()
	playground:add_to("pan", -0.02)
end, 0)

_g_keys:when_greater_than("RIGHT", function()
	playground:add_to("pan", 0.02)
end, 0)
