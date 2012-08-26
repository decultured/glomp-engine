local keyboard = description.workon("glomp_keyboard")
local is_fullscreen = false

keyboard.events:when_equals("F", function()
   	is_fullscreen = not is_fullscreen
   	glomp.window.set_fullscreen(is_fullscreen)
end, 0)

keyboard.events:when_greater_than("Q", glomp.system.exit, 0)
print("Dont't forget to change the exit button!")