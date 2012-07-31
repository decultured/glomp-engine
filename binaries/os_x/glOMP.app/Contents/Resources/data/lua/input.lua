function _glomp_key_pressed(key)
    -- print ("Key pressed from lua:", key)
end

function _glomp_key_released(key)
    if key == glomp_keys.R or key == glomp_keys.r then
    	glomp_load_libs()
    end

    if key == glomp_keys.U or key == glomp_keys.u then
    	print("updates: "..glomp_update_count)
    end

    if key == glomp_keys.Q or key == glomp_keys.q then
    	__glomp_terminate()
    end

    if key == glomp_keys.I or key == glomp_keys.i then
        dofile(LUA_PATH.."input.lua")
    end

    if key == glomp_keys.BACKSPACE then
        dofile(LUA_PATH.."model.lua")
        dofile(LUA_PATH.."model_tests.lua")
        dofile(LUA_PATH.."app_testing.lua")
    end        

end

function _glomp_mouse_moved(x, y)
    print_more("mouse.moved", "Mouse Moving", x, y);
    -- print ("Mouse moved from lua:", x, y)
end

function _glomp_mouse_dragged(x, y, button)
    print_more("mouse.dragged", "Mouse Dragged", x, y - 30);
    -- print ("Mouse dragged from lua:", x, y, button)
end

function _glomp_mouse_pressed(x, y, button)
    print_more("mouse.pressed", "Mouse Clicked", x, y);
    -- print ("Mouse pressed from lua:", x, y, button)
end

function _glomp_mouse_released(x, y, button)
    print_more("mouse.released", "Mouse Released", x, y + 30);
    -- print ("Mouse released from lua:", x, y, button)
end

