local mouse = description.workon("glomp_mouse")

local clear_hex = glomp.graphics.clear_hex
local screen_size = glomp.window.get_screen_size
local window_size = glomp.window.get_size

local timer = description.workon("glomp_time"):set({
								frame_time = 0,
								update_count = 0,
								total_time = 0,
							})

function delay(callback, seconds)
	
	local start_time = timer:get("total_time")
	local closure

	local done = function ()
		timer.events:off("total_time", closure)
	end

	closure = function ()
		print(timer:get("total_time"), start_time, seconds, closure)
		if timer:get("total_time") - start_time > seconds then
			callback()
			done()
		end
	end

	print(timer:get("total_time"), start_time, seconds, closure)
	timer.events:on("total_time", closure)
end

local window = description.workon("glomp_window"):set({
								width = 0,
								height = 0,
								entered = 1,
								clear_color = 0xfdf6e3
							})

local w, h = window_size()
window:set({width = w, height = h})

function _glomp_window_resized(w, h)
    window:set({width = w, height = h})
	window.events:trigger("resized", window.fields, window)
end

function _glomp_window_entry(state)
	window:set({entered = state})
end

function _glomp_update(frame_time)
	frame_time = frame_time or 0
	timer:set({
			frame_time = frame_time,
			total_time = timer:get("total_time") + frame_time,
			update_count = timer:get("update_count") + 1
		})
	window.events:trigger("update", window.fields, window)
end

function _glomp_draw()
	if window:get("clear_color") then
		clear_hex(window:get("clear_color"))
	else
		clear_hex(0x000000)
	end
	window.events:trigger("draw", window.fields, window)
end
