local _g_keys = glomp.description:fetch_or_create("glomp_keyboard")
local _is_fullscreen = false

_g_keys:when_equals("F", function()
   	_is_fullscreen = not _is_fullscreen
   	glomp.window.set_fullscreen(_is_fullscreen)
end, 0)

_g_keys:when_greater_than("Q", function()
    glomp.system.exit()
end, 0)
