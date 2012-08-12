local graphics = graphics
local glomp = glomp or {}
glOMP = glOMP or {}
glOMP.Description = glOMP.Description or {}

glomp.time = glOMP.Description:load("glOMP_time", {
								last_frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

glomp.window = glOMP.Description:load("glOMP_window", {
								w = 0,
								h = 0,
								entered = 1,
								clear_color = "#fdf6e3"
							})

local g_time = glomp.time
local g_window = glomp.window

function _glOMP_window_resized(w, h)
    g_window:set({w = w, h = h})
end

function _glOMP_window_entry(state)
   g_window:set({entered = state})
end

local new_img = glOMP.image.load("assets/images/openFrameworks.png")

function _glOMP_update(frame_time)
	g_time:set({
			frame_time = frame_time,
			total_time = g_time:get("total_time") + frame_time,
			update_count = g_time:get("update_count") + 1
		})
end

local g_root = glOMP.View:load("glOMP_root")

function _glOMP_draw()
	glOMP.graphics.clear(hex_to_rgb(g_window:get("clear_color")))

	g_root:render()

	glOMP.graphics.set_color(hex_to_rgb("#ede9d6"))
	glOMP.graphics.draw_fills(true)
	glOMP.graphics.enable_smoothing()
	glOMP.graphics.rectangle(10, 10, 500, 200)
	glOMP.graphics.draw_fills(false)
	glOMP.graphics.set_circle_resolution(100)
	glOMP.graphics.set_line_width(3)
	glOMP.graphics.set_color(hex_to_rgb("#5a6e75"))
	glOMP.graphics.rectangle(10, 10, 500, 200)

	glOMP.graphics.enable_alpha_blending()
		glOMP.graphics.set_color(hex_to_rgb("#FFFFFF"))
		new_img:draw(30, 30)
	glOMP.graphics.disable_alpha_blending()

	glOMP.graphics.set_color(hex_to_rgb("#5a6e75"))

	if fnt then 
		fnt:draw("WASSUP", 50, 50)
	end
end
