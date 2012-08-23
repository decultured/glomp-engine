local keyboard = description.workon("glomp_keyboard", {})
local mouse = description.workon("glomp_mouse", {
                    x = 0,
                    y = 0,
                })

for k, v in pairs(inv_glomp_keys) do
    keyboard:set(v, 0)
end

for k, v in pairs(inv_mouse_buttons) do
    mouse:set(v, 0)
end

function _glomp_key_pressed(key)
    key = inv_glomp_keys[key] or key
    keyboard:set(key, keyboard:get(key, 0) + 1)
end

function _glomp_key_released(key)
    key = inv_glomp_keys[key]
    keyboard:set(key, 0)
end

function _glomp_mouse_moved(x, y)
    mouse:set({
            x = x,
            y = y
        })
end

function _glomp_mouse_dragged(x, y, button)
    button = inv_mouse_buttons[button]
    
    mouse:set({
            x = x,
            y = y,
            [button] = mouse:get(button, 0) + 1
        })
end

function _glomp_mouse_pressed(x, y, button)
    button = inv_mouse_buttons[button]
    
    mouse:set({
            x = x,
            y = y,
            [button] = mouse:get(button, 0) + 1
        })
end

function _glomp_mouse_released(x, y, button)
    button = inv_mouse_buttons[button]
    
    mouse:set({
            x = x,
            y = y,
            [button] = 0
        })
end

