glomp = glomp or {}

glomp.keyboard = Description.new()


glomp.mouse = Description.new({
                    x = 0,
                    y = 0,
                })

g_keyboard = glomp.keyboard
g_mouse = glomp.mouse

for k, v in pairs(inv_glomp_keys) do
    g_keyboard:set(v, 0)
end

for k, v in pairs(inv_mouse_buttons) do
    g_mouse:set(v, 0)
end

function _glomp_key_pressed(key)
    g_keyboard:set(inv_glomp_keys[key], g_keyboard:get(inv_glomp_keys[key]) + 1)
end

function _glomp_key_released(key)

    if g_keyboard:get("R") > 0 then
    	glomp_load_libs()
    end

    if g_keyboard:get("U") > 0 then
    	print("updates: "..glomp_update_count)
    end

    if g_keyboard:get("Q") > 0 then
    	__glomp_terminate()
    end

    if g_keyboard:get("I") > 0 then
        dofile("input")
    end

    if g_keyboard:get("SPACE") > 0 then
        glomp_load_libs()
        glomp_run_stuff()
    end        

    g_keyboard:set(inv_glomp_keys[key], 0)
end

function _glomp_mouse_moved(x, y)
    g_mouse:set({
            x = x,
            y = y
        })
end

function _glomp_mouse_dragged(x, y, button)
    g_mouse:set({
            x = x,
            y = y
        })

    g_mouse:set(inv_mouse_buttons[button], g_mouse:get(inv_mouse_buttons[button]) + 1)
end

function _glomp_mouse_pressed(x, y, button)
    -- print_more("mouse.pressed", "Mouse Clicked", x, y);
    -- print ("Mouse pressed from lua:", x, y, button)
end

function _glomp_mouse_released(x, y, button)
    -- print_more("mouse.released", "Mouse Released", x, y + 30);
    -- print ("Mouse released from lua:", x, y, button)
end

