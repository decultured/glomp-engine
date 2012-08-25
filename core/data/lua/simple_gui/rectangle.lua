local theme_desc = description.workon("simple_gui_active_theme", "simple_gui_theme")
local theme_vals = theme_desc:all()

local rectangle = definition.workon("simple_gui_rectangle", "simple_gui_element")

local draw_fills        = glomp.graphics.draw_fills
local draw_rectangle    = glomp.graphics.rectangle
local set_color_hex     = glomp.graphics.set_color_hex
local set_line_width    = glomp.graphics.set_line_width

rectangle.defaults.x = 0
rectangle.defaults.y = 0
rectangle.defaults.width   = 100
rectangle.defaults.height  = 100
rectangle.defaults.border_width = theme_vals.line_width
rectangle.defaults.border_color = theme_vals.main_color
rectangle.defaults.background_color = theme_vals.component_bg

rectangle.default_events:on("draw", function (data, context)
                props = context:all()
                draw_fills(true)
                set_color_hex(props.background_color)
                draw_rectangle(props.x, props.y, props.width, props.height)
                draw_fills(false)
                set_line_width(props.border_width)
                set_color_hex(props.border_color)
                draw_rectangle(props.x, props.y, props.width, props.height)
            end)
