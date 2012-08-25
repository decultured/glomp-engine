local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local normal_init       = definition.workon("simple_gui_button_normal_init", "simple_gui_rectangle")
normal_init.defaults.color = theme_vals.highlight_color
normal_init.defaults.border_color = theme_vals.white

local pressed_init      = definition.workon("simple_gui_button_pressed_init", "simple_gui_rectangle")
pressed_init.defaults.color = theme_vals.active_color
pressed_init.defaults.border_color = theme_vals.white

local hover_init        = definition.workon("simple_gui_button_hover_init", "simple_gui_rectangle")
hover_init.defaults.color = theme_vals.cyan
hover_init.defaults.border_color = theme_vals.white

local disabled_init     = definition.workon("simple_gui_button_disabled_init", "simple_gui_rectangle")
disabled_init.defaults.color = theme_vals.disabled_color
disabled_init.defaults.border_color = theme_vals.white

local button = definition.workon("simple_gui_button", "simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate

button.defaults.x       = 0
button.defaults.y       = 0
button.defaults.width   = 100
button.defaults.height  = 100
button.defaults.text    = "Button"
button.defaults.fit_text    = true
button.defaults.padding_top     = 5
button.defaults.padding_bottom  = 5
button.defaults.padding_left    = 5
button.defaults.padding_right   = 5

button.defaults.normal_rect     = nil
button.defaults.hover_rect      = nil
button.defaults.pressed_rect    = nil
button.defaults.disabled_rect   = nil

button.defaults.label       = nil
button.defaults.rectangle   = nil

button.defaults.disabled    = false

button.events:on("apply", function (def, context)
    local normal_rect   = description.workon(context.name.."_normal_rect",      "simple_gui_button_normal_init")
    local hover_rect    = description.workon(context.name.."_hover_rect",       "simple_gui_button_hover_init")
    local pressed_rect  = description.workon(context.name.."_pressed_rect",     "simple_gui_button_pressed_init")
    local disabled_rect = description.workon(context.name.."_disabled_rect",    "simple_gui_button_disabled_init")
    local label         = description.workon(context.name.."_label",            "simple_gui_label")

    label.events:on("changed", function (width, label_context)
        if not context:get("fit_text") then
            return
        end

        local label_props = label_context:all()
        local props = context:all()
        context:set("width", label_props.width + props.padding_left + props.padding_right)
        context:set("height", label_props.height + props.padding_top + props.padding_bottom)
    end)

    context:set({
        normal_rect     = normal_rect,
        hover_rect      = hover_rect,
        pressed_rect    = pressed_rect,
        disabled_rect   = disabled_rect,

        rectangle = normal_rect,
        label     = label
    })

end)

button.default_events:on("changed", function (data, context)
    local props = context:all()
    if props.label then
        props.label:set({
                x = props.padding_left,
                y = props.padding_top + props.label:get("height"),
                text = props.text,
                color = (props.rectangle and props.rectangle:get("border_color")) or props.color
            })
    end

    if props.rectangle then 
        props.rectangle:set({
                x       = 0,
                y       = 0,
                width   = props.width,
                height  = props.height
            })
    end
end)

button.default_events:on("mouse_over", function (data, context)
    if context:get("disabled") then
        return
    end
    context:set("rectangle", context:get("hover_rect"))
end)

button.default_events:on("mouse_out", function (data, context)
    if context:get("disabled") then
        return
    end
    context:set("rectangle", context:get("normal_rect"))
end)

button.default_events:on("mouse_down", function (data, context)
    if context:get("disabled") then
        return
    end

    if data then
        context:set("rectangle", context:get("pressed_rect"))
    else
        context:set("rectangle", context:get("normal_rect"))
        context.events:trigger("click", data, context)
    end
end)

button.default_events:on("disabled", function (data, context)
    if data then
        context:set("rectangle", "disabled_rect")
    elseif context:get("mouse_down") then
        context:set("rectangle", "pressed_rect")
    elseif context:get("hover") then
        context:set("rectangle", "hover_rect")
    else
        context:set("rectangle", "normal_rect")
    end
end)

button.default_events:on("draw", function (data, context)
        local props = context:all()

        push_matrix()
        translate(props.x, props.y)
        
        props.rectangle.events:trigger("draw", context, props.rectangle)
        props.label.events:trigger("draw", context, props.label)

        pop_matrix()
    end)
