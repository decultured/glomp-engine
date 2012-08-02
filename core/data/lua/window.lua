function _glomp_window_resized(w, h)
    -- print ("Window resized from lua:", w, h)
end

function _glomp_window_entry(state)
    print_more("window_entry", "Window entry:" .. state, 700, 160)
end

last_frame_time = 0
glomp_update_count = 0
total_elapsed_time = 0

function _glomp_update(frame_time)
	elapsed_time = frame_time
	total_elapsed_time = total_elapsed_time + frame_time

	glomp_update_count = glomp_update_count + 1

	print_more("update.count", "Updates: " .. glomp_update_count, 700, 40)
	print_more("update.time", "Elapsed: " .. elapsed_time, 700, 60)
	print_more("update.time_avg", "Average: " .. total_elapsed_time / glomp_update_count, 700, 80)
	print_more("update.fps", "FPS: " .. glomp_update_count / total_elapsed_time, 700, 100)
	print_more("update.total", "Total: " .. total_elapsed_time, 700, 120)
end