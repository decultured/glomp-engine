print("Loading Glomp Lua Libraries")

function _glomp_key_pressed(key)
    print ("Key pressed from lua:", key)
end

function _glomp_key_released(key)
    print ("Key released from lua:", key)
end

function _glomp_mouse_moved(x, y)
    print ("Mouse moved from lua:", x, y)
end

function _glomp_mouse_dragged(x, y, button)
    print ("Mouse dragged from lua:", x, y, button)
end

function _glomp_mouse_pressed(x, y, button)
    print ("Mouse pressed from lua:", x, y, button)
end

function _glomp_mouse_released(x, y, button)
    print ("Mouse released from lua:", x, y, button)
end

function _glomp_window_resized(w, h)
    print ("Window resized from lua:", w, h)
end