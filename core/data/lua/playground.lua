local fnt = glomp.font.load("assets/fonts/Cousine-Regular.ttf", 12, true, false, true, 0.9, 100)

local keyboard = glomp.description:fetch_or_create("glomp_keyboard")
local time = glomp.description:fetch_or_create("glomp_time")
-- local root = glomp.view:fetch_or_create("root")

local new_img = glomp.image.load("assets/images/openFrameworks.png")

-- images = {}

-- for counter = 1,3000 do
-- 	local new_image = glomp.gui.image:fetch_or_create("image_test_" .. tostring(counter))

-- 	new_image.x = math.random(100, 800)
-- 	new_image.y = math.random(100, 600)
-- 	new_image.image = new_img

-- 	root:add_child(new_image)
-- end

-- local performance = glomp.gui.label:fetch_or_create("debug_performance_display")

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
