local fnt = glOMP.font.load("assets/fonts/Cousine-Regular.ttf", 12, true, false, true, 0.9, 100)

local _g_keys = glOMP.Description:load("glOMP_keyboard")
local _g_time = glOMP.Description:load("glOMP_time")

_g_time:on("frame_time", function (frames, g_time)
	-- TODO : this is *massively* inefficient
	-- print_more("update.count", "Updates: " .. g_time:get("update_count"), 700, 40)
	-- print_more("update.time", "Elapsed: " .. g_time:get("frame_time"), 700, 60)
	-- print_more("update.time_avg", "Average: " .. g_time:get("total_time") / g_time:get("update_count"), 700, 80)
	-- print_more("update.fps", "FPS: " .. g_time:get("update_count") / g_time:get("total_time"), 700, 100)
	-- print_more("update.total", "Total: " .. g_time:get("total_time"), 700, 120)
end)

local _performance_display = glOMP.View:load("debug_performance_display")

function _performance_display:draw()
	fnt:draw_string("Updates: " .. _g_time:get("update_count"), 700, 40)
	fnt:draw_string("Elapsed: " .. _g_time:get("frame_time"), 700, 60)
	fnt:draw_string("Average: " .. _g_time:get("total_time") / _g_time:get("update_count"), 700, 80)
	fnt:draw_string("FPS: " .. _g_time:get("update_count") / _g_time:get("total_time"), 700, 100)
	fnt:draw_string("Total: " .. _g_time:get("total_time"), 700, 120)
end

local _g_root = glOMP.View:load("root")

_g_root:add_child(_performance_display)