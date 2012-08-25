local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local gui_element = definition.workon("simple_gui_element")

local draw_fills        = glomp.graphics.draw_fills
local draw_rectangle    = glomp.graphics.rectangle
local set_color_hex     = glomp.graphics.set_color_hex
local set_line_width    = glomp.graphics.set_line_width

gui_element.defaults.x          = 0
gui_element.defaults.y          = 0
gui_element.defaults.width      = 100
gui_element.defaults.height     = 100
gui_element.defaults.color      = theme_vals.main_color

gui_element.events:on("apply", function(data, context)
        data:set("children", collection.workon(data.name .. "_children"))
    end)

gui_element.default_events:on("test_mouse_down", function (data, context)
        
    end)

gui_element.default_events:on("test_mouse_up", function (data, context)

    end)

gui_element.default_events:on("test_mouse_moved", function (data, context)

    end)

gui_element.default_events:on("test_mouse_dragged", function (data, context)

    end)
