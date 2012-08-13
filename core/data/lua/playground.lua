local fnt = glOMP.font.load("assets/fonts/Cousine-Regular.ttf", 12, true, false, true, 0.9, 100)

local keyboard = glOMP.Description:load("glOMP_keyboard")
local time = glOMP.Description:load("glOMP_time")
local root = glOMP.View:get_or_create("root")

local new_img = glOMP.image.load("assets/images/openFrameworks.png")

images = {}

for counter = 1,10000 do
	local new_image = glOMP.gui.Image:get_or_create("image_test_" .. tostring(counter))

	new_image.x = math.random(100, 800)
	new_image.y = math.random(100, 600)
	new_image.image = new_img

	root:add_child(new_image)
end

local performance = glOMP.gui.Label:get_or_create("debug_performance_display", {
																			text = "testing",
																			font = fnt,
																			color = "#ff0000",
																			x = 700,
																			y = 40,
																			visible = false
																		})

root:add_child(performance)

keyboard:when_equals("T", function()
		performance.visible = not performance.visible
	end, 0)

time:on("update_count", function()
		local time_data = time:all()

		local text = string.format("Updates: %d\nElapsed: %f\nAverage: %f\nRunning: %f\nFPS: %d",
					time_data["update_count"],
					time_data["frame_time"],
					time_data["total_time"] / time_data["update_count"],
					time_data["total_time"],
					time_data["update_count"] / time_data["total_time"])

		performance.text = text
	end, 0)
