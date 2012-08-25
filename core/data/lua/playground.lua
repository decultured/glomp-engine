local fnt = glomp.font.load("assets/fonts/Cousine-Regular.ttf", 12, true, false, true, 0.9, 100)
local keyboard = description.workon("glomp_keyboard")
local time = description.workon("glomp_time")
local window = description.workon("glomp_window")

local new_img = glomp.image.load("assets/images/openFrameworks.png")

local gui_root = description.workon("gui_root", "simple_gui_root")

for counter = 1,3000 do
	local props = 	{
						x = math.random(100, 800),
						y = math.random(100, 600),
						image = new_img,
						text = "this is text!"
					}

	local new_image = description.workon("image_test_" .. counter, "simple_gui_image"):set(props)
	gui_root:get("children"):add(new_image)
end

window.events:on("draw", function (data, caller) 
		gui_root.events:trigger("draw", gui_root, gui_root)
	end)

local performance = description.workon("debug_performance_display", "simple_gui_label")

performance:set({
		x = 700,
		y = 40,
		color = 0xff0000,
		visible = false
	})

gui_root:get("children"):add(performance)

keyboard.events:when_equals("T", function()
		performance:toggle("visible")
	end, 0)

time.events:on("update_count", function()
		local time_data = time:all()

		local text = string.format("Updates: %d\nElapsed: %f\nAverage: %f\nRunning: %f\nFPS: %d",
					time_data["update_count"],
					time_data["frame_time"],
					time_data["total_time"] / time_data["update_count"],
					time_data["total_time"],
					time_data["update_count"] / time_data["total_time"])

		performance:set("text", text)
	end, 0)
