local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local root = definition.workon("simple_gui_root", "simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate
local scale             = glomp.graphics.scale

root.defaults.width     = 800
root.defaults.height    = 600
root.defaults.x         = 0
root.defaults.y         = 0
root.defaults.scale_x   = 1
root.defaults.scale_y   = 1

root.default_events:on("draw", function (data, context)
        props = context:all()

        push_matrix()

        translate(props.x, props.y)
        scale(props.scale_x, props.scale_y)

        props.children:trigger_all("draw", context)

        pop_matrix()
    end)