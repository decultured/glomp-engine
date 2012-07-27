function _glomp_window_resized(w, h)
    -- print ("Window resized from lua:", w, h)
end

glomp_update_count = 0
function _glomp_update()
	glomp_update_count = glomp_update_count + 1
end