local keyboard  = description.workon("glomp_keyboard")
local mouse     = description.workon("glomp_mouse")
local time      = description.workon("glomp_time")
local window    = description.workon("glomp_window")

local theme_vals    = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()
local root_window   = description.workon("root_window", "simple_gui_root")
local performance   = description.workon("debug_performance_display", "simple_gui_label")

performance:set({
        top = 20,
        left = 20,
        visible = false,
        font = theme_vals.tiny_font,
        color = theme_vals.orange,
        align = "left",
        v_align = "top"
    })

keyboard.events:when_equals("T", function()
        performance:toggle("visible")
    end, 0)

time.events:on("update_count", function()
        if not performance:get("visible") then
            return
        end

        local time_data = time:all()

        local text = string.format("Updates: %d\nElapsed: %f\nAverage: %f\nRunning: %f\nFPS: %6d",
                    time_data["update_count"],
                    time_data["frame_time"],
                    time_data["total_time"] / time_data["update_count"],
                    time_data["total_time"],
                    1.0 / (time_data["average_frame_time"] or 1000000))

        performance:set("text", text)
    end, 0)