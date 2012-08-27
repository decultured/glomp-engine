local theme_desc = description.workon("simple_gui_active_theme", "simple_gui_theme")
local theme_vals = theme_desc:all()

local food = definition.workon("game_food", "simple_gui_element")

local draw_fills        = glomp.graphics.draw_fills
local draw_rectangle    = glomp.graphics.rectangle
local set_color_hex     = glomp.graphics.set_color_hex
local set_line_width    = glomp.graphics.set_line_width

food.defaults.x = 0
food.defaults.y = 0
food.defaults.width   = 100
food.defaults.height  = 100
food.defaults.border_width = theme_vals.line_width
food.defaults.border_color = theme_vals.main_color
food.defaults.color = theme_vals.component_bg

food.default_events:on("draw", function (data, context)
                props = context:all()
                draw_fills(true)
                draw_rectangle(0, 0, props.width, props.height)
                draw_fills(false)
                set_line_width(props.border_width)
                set_color_hex(props.border_color)
                draw_rectangle(0, 0, props.width, props.height)
            end)

