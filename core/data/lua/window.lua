local graphics = graphics
local glomp = glomp or {}
glOMP.Description = glOMP.Description or {}

local _g_time = glOMP.Description:load("glOMP_time", {
								frame_time = 0,
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

function _glOMP_update(frame_time)
	_g_time:set({
			frame_time = frame_time,
			total_time = _g_time:get("total_time") + frame_time,
			update_count = _g_time:get("update_count") + 1
		})
end

local g_root = glOMP.View:get_or_create("root")

function _glOMP_draw()
	glOMP.graphics.clear(hex_to_rgb(_g_window:get("clear_color")))
	g_root:render()
end
