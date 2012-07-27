function _glomp_window_resized(w, h)
    -- print ("Window resized from lua:", w, h)
end

glomp_update_count = 0
function _glomp_update()
	print_more("updates", "Updates " .. glomp_update_count, x, y - 30);
	glomp_update_count = glomp_update_count + 1
end