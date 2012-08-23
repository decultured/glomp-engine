local fnt = glomp.font.load("assets/fonts/Cousine-Regular.ttf", 12, true, false, true, 0.9, 100)
local keyboard = description.workon("glomp_keyboard")
local time = description.workon("glomp_time")
-- local root = glomp.view.workon("root")

local new_img = glomp.image.load("assets/images/openFrameworks.png")

images = {}

for counter = 1,3 do
	local props = 	{
						x = math.random(100, 800),
						y = math.random(100, 600),
						image = new_img
					}

	local new_image = description.workon("image_test_" .. tostring(counter)):set(props)
end

-- local performance = glomp.gui.label.workon("debug_performance_display")

-- performance.font = fnt
-- performance.color = "#ff0000"
-- performance.x = 700
-- performance.y = 40
-- performance.visible = false

-- root:add_child(performance)

-- keyboard:when_equals("T", function()
-- 		performance.visible = not performance.visible
-- 	end, 0)

-- time:on("update_count", function()
-- 		local time_data = time:all()

-- 		local text = string.format("Updates: %d\nElapsed: %f\nAverage: %f\nRunning: %f\nFPS: %d",
-- 					time_data["update_count"],
-- 					time_data["frame_time"],
-- 					time_data["total_time"] / time_data["update_count"],
-- 					time_data["total_time"],
-- 					time_data["update_count"] / time_data["total_time"])

-- 		performance.text = text
-- 	end, 0)
