local _g_keys = glOMP.Description:load("glOMP_keyboard")
local _is_fullscreen = false

_g_keys:when_equals("F", function()
   	_is_fullscreen = not _is_fullscreen
   	glOMP.window.set_fullscreen(_is_fullscreen)
end, 0)

_g_keys:when_greater_than("Q", function()
    glOMP.system.exit()
end, 0)
