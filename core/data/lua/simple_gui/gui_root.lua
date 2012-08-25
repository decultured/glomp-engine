local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local root = definition.workon("simple_gui_root", "simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate
local scale             = glomp.graphics.scale

root.defaults.container_width   = 1000
root.defaults.container_height  = 1000
root.defaults.offset_x          = 0
root.defaults.offset_y          = 0


label.default_events:on("draw", function (data, context)
        props = context:all()

        push_matrix()
        translate(props.x, props.y)

        set_color_hex(props.color)
        if props.font then
            props.font:draw_string(props.display_text)
        else
            print_string(props.display_text)
        end

        pop_matrix()
    end)
