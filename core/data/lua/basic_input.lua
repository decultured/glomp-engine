local keyboard = glomp.description:fetch_or_create("glomp_keyboard")
local is_fullscreen = false

keyboard.events:when_equals("F", function()
   	is_fullscreen = not is_fullscreen
   	glomp.window.set_fullscreen(is_fullscreen)
end, 0)

keyboard.events:when_greater_than("Q", function()
    glomp.system.exit()
end, 0)
