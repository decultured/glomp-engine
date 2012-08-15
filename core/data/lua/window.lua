local graphics = graphics
local glomp = glomp or {}
glomp.description = glomp.description or {}

local _g_time = glomp.description:fetch_or_create("glomp_time", {
								frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

local _g_window = glomp.description:fetch_or_create("glomp_window", {
								w = 0,
								h = 0,
								entered = 1,
								clear_color = "#fdf6e3"
							})

function _glomp_window_resized(w, h)
    _g_window:set({w = w, h = h})
end

function _glomp_window_entry(state)
   _g_window:set({entered = state})
end

function _glomp_update(frame_time)
	_g_time:set({
			frame_time = frame_time,
			total_time = _g_time:get("total_time") + frame_time,
			update_count = _g_time:get("update_count") + 1
		})
end

local g_root = glomp.view:fetch_or_create("root")

function _glomp_draw()
	glomp.graphics.clear(hex_to_rgb(_g_window:get("clear_color")))

	g_root:render()
end
