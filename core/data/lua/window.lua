local mouse = description.workon("glomp_mouse")

local clear_hex = glomp.graphics.clear_hex
local screen_size = glomp.window.get_screen_size
local window_size = glomp.window.get_size

local timer = description.workon("glomp_time"):set({
								frame_time = 0,
								update_count = 0,
								total_time = 0,
								average_frame_time = 0
							})

function delay(callback, seconds)
	
	local start_time = timer:get("total_time")
	local closure

	local done = function ()
		timer.events:off("total_time", closure)
	end

	closure = function ()
		if timer:get("total_time") - start_time > seconds then
			callback()
			done()
		end
	end

	timer.events:on("total_time", closure)
end

function tick(callback, seconds)
	
	local start_time = timer:get("total_time")
	local closure

	local done = function ()
		timer.events:off("total_time", closure)
	end

	closure = function ()
		if timer:get("total_time") - start_time > seconds then
			if callback() then
				done()
			else
				start_time = start_time + seconds
			end
		end
	end

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

local frames = {}
local frame_samples = 100
for i = 1, frame_samples do
	frames[i] = 100
end
local frame = 1
local average_frame_time = 0

function _glomp_update(frame_time)
	frame_time = frame_time or 0
	
	frames[frame] = frame_time
	frame = frame + 1
	if frame > frame_samples then
		frame = 1
	end

	average_frame_time = 0
	for i = 1, frame_samples do
		average_frame_time = average_frame_time + frames[i]
	end
	average_frame_time = average_frame_time / frame_samples

	timer:set({
			frame_time = frame_time,
			total_time = timer:get("total_time") + frame_time,
			update_count = timer:get("update_count") + 1,
			average_frame_time = average_frame_time
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
