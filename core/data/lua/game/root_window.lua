local keyboard  = description.workon("glomp_keyboard")
local mouse     = description.workon("glomp_mouse")
local time      = description.workon("glomp_time")
local window    = description.workon("glomp_window")

local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local root_window  = description.workon("root_window", "simple_gui_root")
root_window:set({
        width = window:get("width"),
        height = window:get("height"),
    })

window.events:on("resized", function (fields, window)
    root_window:set({
            width = fields.width,
            height = fields.height
        })
end)

local pressed = false
local released = false

window.events:on("update", function (data, window)
        root_window:calc_transforms()
        root_window:test_mouse(mouse, pressed, released)
        root_window.events:trigger("update", time, root_window)
        pressed, released = false, false
    end)


window.events:on("draw", function (data, caller) 
        root_window.events:trigger("render", root_window, root_window)
    end)

mouse.events:on("moved", function (data, caller)

end)

mouse.events:on("dragged", function (data, caller)
    root_window.events:trigger("test_mouse_dragged", caller:all(), root_window)
end)

mouse.events:on("pressed", function (data, caller)
    pressed = true
end)

mouse.events:on("released", function (data, caller)
    released = true
end)
