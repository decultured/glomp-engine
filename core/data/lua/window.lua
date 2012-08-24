local graphics = graphics


local timer = description.workon("glomp_time", {
								frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

local window = description.workon("glomp_window", {
								w = 0,
								h = 0,
								entered = 1,
								clear_color = "#fdf6e3"
							})

function _glomp_window_resized(w, h)
    window:set({w = w, h = h})
	window.events:trigger("resized")
end

function _glomp_window_entry(state)
	window:set({entered = state})
end

function _glomp_update(frame_time)
	timer:set({
			frame_time = frame_time,
			total_time = timer:get("total_time") + frame_time,
			update_count = timer:get("update_count") + 1
		})
	window.events:trigger("update")
end

function _glomp_draw()
	glomp.graphics.clear(hex_to_rgb(window:get("clear_color")))
	window.events:trigger("draw")
end
