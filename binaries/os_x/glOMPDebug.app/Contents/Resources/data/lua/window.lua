function _glomp_window_resized(w, h)
    -- print ("Window resized from lua:", w, h)
end

glomp_update_count = 0
function _glomp_update()
	print_more("update.count", "Updates: " .. glomp_update_count, 50, 50)
	glomp_update_count = glomp_update_count + 1
end