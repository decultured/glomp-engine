function _glomp_key_pressed(key)
    -- print ("Key pressed from lua:", key)
end

function _glomp_key_released(key)
    if key == glomp_keys.R then
    	glomp_load_libs()
    end

    if key == glomp_keys.U then
    	print("updates: "..glomp_update_count)
    end
end

function _glomp_mouse_moved(x, y)
    -- print ("Mouse moved from lua:", x, y)
end

function _glomp_mouse_dragged(x, y, button)
    -- print ("Mouse dragged from lua:", x, y, button)
end

function _glomp_mouse_pressed(x, y, button)
    -- print ("Mouse pressed from lua:", x, y, button)
end

function _glomp_mouse_released(x, y, button)
    -- print ("Mouse released from lua:", x, y, button)
end