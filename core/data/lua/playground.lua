snd = sound.new("assets/know.mp3", true)
fnt = font.new("assets/fonts/Cousine-Regular.ttf", 30, true, false, true, 0.9, 100)

local playground = Description.new({
		offset = 0,
		speed = 1,
		pan = 0
	})


glomp.keyboard:on("change:A", function(data) 
	if data == 1 then
		snd:play()
		snd:set_position(playground:get("offset"))
	elseif data == 0 then
		playground:set("offset", snd:get_position())
		snd:stop()
	end
end)

glomp.keyboard:on("change:UP", function(data) 
	if data > 0 then
		playground:set("speed", playground:get("speed") + 0.02)
		snd:set_speed(playground:get("speed"))
	end
end)

glomp.keyboard:on("change:DOWN", function(data) 
	if data > 0 then
		playground:set("speed", playground:get("speed") - 0.02)
		snd:set_speed(playground:get("speed"))
	end
end)


glomp.keyboard:on("change:LEFT", function(data)
	if data > 0 then
		playground:set("pan", playground:get("pan") - 0.02)
		snd:set_pan(playground:get("pan"))
	end
end)

glomp.keyboard:on("change:RIGHT", function(data)
	if data > 0 then
		playground:set("pan", playground:get("pan") + 0.02)
		snd:set_pan(playground:get("pan"))
	end
end)
