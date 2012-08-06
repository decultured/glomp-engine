snd = sound.new("assets/beat.wav", true)
fnt = font.new("assets/fonts/Cousine-Regular.ttf", 30, true, false, true, 0.9, 100)


glomp.keyboard:on("change:A", function(data) 
	if data == 1 then
		snd:play()
	elseif data == 0 then
		snd:stop()
	end
end)