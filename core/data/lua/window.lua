local graphics = graphics
local glomp = glomp or {}
local Description = Description

glomp.time = Description.new({
								last_frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

glomp.window = Description.new({
								w = 0,
								h = 0,
								entered = 1,
							})

local g_time = glomp.time
local g_window = glomp.window

function _glomp_window_resized(w, h)
    g_window:set({w = w, h = h})
end

function _glomp_window_entry(state)
   g_window:set({entered = state})
end

local new_img = image.new("assets/images/openFrameworks.png")

function _glomp_update(frame_time)
	g_time:set({
			frame_time = frame_time,
			total_time = g_time:get("total_time") + frame_time,
			update_count = g_time:get("update_count") + 1
		})
end

function _glomp_draw()
	graphics.clear(hex_to_rgb("#fdf6e3"))

	graphics.set_color(hex_to_rgb("#ede9d6"))
	graphics.draw_fills(true)
	graphics.enable_smoothing()
	graphics.rectangle(10, 10, 500, 200)
	graphics.draw_fills(false)
	graphics.set_circle_resolution(100)
	graphics.set_line_width(3)
	graphics.set_color(hex_to_rgb("#5a6e75"))
	graphics.rectangle(10, 10, 500, 200)

	graphics.enable_alpha_blending()
		graphics.set_color(hex_to_rgb("#FFFFFF"))
		new_img:draw(30, 30)
	graphics.disable_alpha_blending()

	graphics.set_color(hex_to_rgb("#5a6e75"))

	if fnt then 
		fnt:draw("WASSUP", 50, 50)
	end
end
