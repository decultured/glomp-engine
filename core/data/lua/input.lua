glomp = glomp or {}
glOMP = glOMP or {}
glOMP.Description = glOMP.Description or {}

local _g_keyboard = glOMP.Description:load("glOMP_keyboard", {})


local _g_mouse = glOMP.Description:load("glOMP_mouse", {
                    x = 0,
                    y = 0,
                })

for k, v in pairs(inv_glOMP_keys) do
    _g_keyboard:set(v, 0)
end

for k, v in pairs(inv_mouse_buttons) do
    _g_mouse:set(v, 0)
end

function _glOMP_key_pressed(key)
    key = inv_glOMP_keys[key] or key
    _g_keyboard:set(key, _g_keyboard:get(key, 0) + 1)
end

function _glOMP_key_released(key)
    key = inv_glOMP_keys[key]
    _g_keyboard:set(key, 0)
end

function _glOMP_mouse_moved(x, y)
    _g_mouse:set({
            x = x,
            y = y
        })
end

function _glOMP_mouse_dragged(x, y, button)
    button = inv_mouse_buttons[button]
    
    _g_mouse:set({
            x = x,
            y = y,
            [button] = _g_mouse:get(button, 0) + 1
        })
end

function _glOMP_mouse_pressed(x, y, button)
    button = inv_mouse_buttons[button]
    
    _g_mouse:set({
            x = x,
            y = y,
            [button] = _g_mouse:get(button, 0) + 1
        })
end

function _glOMP_mouse_released(x, y, button)
    button = inv_mouse_buttons[button]
    
    _g_mouse:set({
            x = x,
            y = y,
            [button] = 0
        })
end

