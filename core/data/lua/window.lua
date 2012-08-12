local graphics = graphics
local glomp = glomp or {}
glOMP = glOMP or {}
glOMP.Description = glOMP.Description or {}

local _g_time = glOMP.Description:load("glOMP_time", {
								last_frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

local _g_window = glOMP.Description:load("glOMP_window", {
								w = 0,
								h = 0,
								entered = 1,
								clear_color = "#fdf6e3"
							})

function _glOMP_window_resized(w, h)
    _g_window:set({w = w, h = h})
end

function _glOMP_window_entry(state)
   _g_window:set({entered = state})
end

local new_img = glOMP.image.load("assets/images/openFrameworks.png")

function _glOMP_update(frame_time)
	_g_time:set({
			frame_time = frame_time,
			total_time = _g_time:get("total_time") + frame_time,
			update_count = _g_time:get("update_count") + 1
		})
end

local g_root = glOMP.View:load("root")

function _glOMP_draw()
	glOMP.graphics.clear(hex_to_rgb(_g_window:get("clear_color")))

	g_root:render()


	glOMP.graphics.enable_alpha_blending()
		glOMP.graphics.set_color(hex_to_rgb("#FFFFFF"))
		new_img:draw(30, 30)
	glOMP.graphics.disable_alpha_blending()

	glOMP.graphics.set_color(hex_to_rgb("#5a6e75"))
end
