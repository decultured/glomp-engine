function _glomp_window_resized(w, h)
    -- print ("Window resized from lua:", w, h)
end

function _glomp_window_entry(state)
    print_more("window_entry", "Window entry:" .. state, 700, 160)
end

glomp.g_time = glomp.Description.new({
								last_frame_time = 0,
								update_count = 0,
								total_time = 0,
							})
local g_time = glomp.g_time

-- TODO : Set with table!
g_time:set("last_frame_time", 0)
g_time:set("update_count", 0)
g_time:set("total_time", 0)
g_time:set("frame_time", 0)

function _glomp_update(frame_time)
	-- TODO : Set with table!
	g_time:set("frame_time", frame_time)
	g_time:set("total_time", g_time:get("total_time") + frame_time)
	g_time:set("update_count", g_time:get("update_count") + 1)

	-- TODO : this is *massively* inefficient
	print_more("update.count", "Updates: " .. g_time:get("update_count"), 700, 40)
	print_more("update.time", "Elapsed: " .. g_time:get("frame_time"), 700, 60)
	print_more("update.time_avg", "Average: " .. g_time:get("total_time") / g_time:get("update_count"), 700, 80)
	print_more("update.fps", "FPS: " .. g_time:get("update_count") / g_time:get("total_time"), 700, 100)
	print_more("update.total", "Total: " .. g_time:get("total_time"), 700, 120)
end
