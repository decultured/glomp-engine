local graphics = graphics
local glomp = glomp or {}
local Description = Description

glomp.time = Description.new({
								last_frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

glomp.window = Description.new({
								x = 0,
								y = 0,
								entered = 1,
							})

glomp.clear_color = Description.new({
								r = 0,
								g = 0,
								b = 0
							})

local g_time = glomp.time
local g_window = glomp.window
local g_clear_color = glomp.clear_color
local g_mouse = glomp.mouse


function _glomp_window_resized(w, h)
    g_window:set({w = w, h = h})
end

function _glomp_window_entry(state)
   g_window:set({entered = state})
end

function _glomp_update(frame_time)
	g_time:set({
			frame_time = frame_time,
			total_time = g_time:get("total_time") + frame_time,
			update_count = g_time:get("update_count") + 1
		})

	g_clear_color:set("b", g_time:get("update_count") * 0.1)
	
	-- TODO : this is *massively* inefficient
	print_more("update.count", "Updates: " .. g_time:get("update_count"), 700, 40)
	print_more("update.time", "Elapsed: " .. g_time:get("frame_time"), 700, 60)
	print_more("update.time_avg", "Average: " .. g_time:get("total_time") / g_time:get("update_count"), 700, 80)
	print_more("update.fps", "FPS: " .. g_time:get("update_count") / g_time:get("total_time"), 700, 100)
	print_more("update.total", "Total: " .. g_time:get("total_time"), 700, 120)
	print_more("mouse.moved", "<=", g_mouse:get("x"), g_mouse:get("y"));
end

function _glomp_draw()
	graphics.clear(g_clear_color:get("r"), g_clear_color:get("g"), g_clear_color:get("b"))

	graphics.set_color(0, g_time:get("update_count") * 0.1, 0, 255)
	graphics.draw_fills(true)
	graphics.enable_smoothing()
	graphics.rectangle(10, 10, 500, 200)
	graphics.draw_fills(false)
	graphics.set_circle_resolution(100)
	graphics.set_line_width(3)
	graphics.set_color(100,0,0, 255)
	graphics.rectangle(10, 10, 500, 200)

	if fnt then 
		fnt:draw("WASSUP", 50, 50)
	end
end
