glomp = glomp or {}

glomp.keyboard = Description.new()


glomp.mouse = Description.new({
                    x = 0,
                    y = 0,
                })

local g_keyboard = glomp.keyboard
local g_mouse = glomp.mouse

for k, v in pairs(inv_glomp_keys) do
    g_keyboard:set(v, 0)
end

for k, v in pairs(inv_mouse_buttons) do
    g_mouse:set(v, 0)
end

function _glomp_key_pressed(key)
    key = inv_glomp_keys[key] or key
    g_keyboard:set(key, g_keyboard:get(key, 0) + 1)
end

function _glomp_key_released(key)
    key = inv_glomp_keys[key]
    g_keyboard:set(key, 0)
end

function _glomp_mouse_moved(x, y)
    g_mouse:set({
            x = x,
            y = y
        })
end

function _glomp_mouse_dragged(x, y, button)
    button = inv_mouse_buttons[button]
    
    g_mouse:set({
            x = x,
            y = y,
            [button] = g_mouse:get(button, 0) + 1
        })
end

function _glomp_mouse_pressed(x, y, button)
    button = inv_mouse_buttons[button]
    
    g_mouse:set({
            x = x,
            y = y,
            [button] = g_mouse:get(button, 0) + 1
        })
end

function _glomp_mouse_released(x, y, button)
    button = inv_mouse_buttons[button]
    
    g_mouse:set({
            x = x,
            y = y,
            [button] = 0
        })
end

