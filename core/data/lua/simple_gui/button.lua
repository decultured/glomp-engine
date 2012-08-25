local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local normal_init       = definition.workon("simple_gui_button_normal_init", "simple_gui_rectangle")
normal_init.defaults.color = theme_vals.highlight_color
normal_init.defaults.pct_width = 100
normal_init.defaults.pct_height = 100
normal_init.defaults.border_color = theme_vals.white

local pressed_init      = definition.workon("simple_gui_button_pressed_init", "simple_gui_rectangle")
pressed_init.defaults.color = theme_vals.active_color
pressed_init.defaults.pct_width = 100
pressed_init.defaults.pct_height = 100
pressed_init.defaults.border_color = theme_vals.white

local hover_init        = definition.workon("simple_gui_button_hover_init", "simple_gui_rectangle")
hover_init.defaults.color = theme_vals.cyan
hover_init.defaults.pct_width = 100
hover_init.defaults.pct_height = 100
hover_init.defaults.border_color = theme_vals.white

local disabled_init     = definition.workon("simple_gui_button_disabled_init", "simple_gui_rectangle")
disabled_init.defaults.color = theme_vals.disabled_color
disabled_init.defaults.pct_width = 100
disabled_init.defaults.pct_height = 100
disabled_init.defaults.border_color = theme_vals.white

local button = definition.workon("simple_gui_button", "simple_gui_element")

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
    local props = context:all()

    local normal_rect   = description.workon(context.name.."_normal_rect",      "simple_gui_button_normal_init")
    local hover_rect    = description.workon(context.name.."_hover_rect",       "simple_gui_button_hover_init")
    local pressed_rect  = description.workon(context.name.."_pressed_rect",     "simple_gui_button_pressed_init")
    local disabled_rect = description.workon(context.name.."_disabled_rect",    "simple_gui_button_disabled_init")
    local label         = description.workon(context.name.."_label",            "simple_gui_label")

    label:set({
        font = theme_vals.font,
        text = props.text,
        x = props.padding_left,
        y = props.padding_top,
    })

    context:set({
        normal_rect     = normal_rect,
        hover_rect      = hover_rect,
        pressed_rect    = pressed_rect,
        disabled_rect   = disabled_rect,

        label     = label,
        rectangle = normal_rect,
    })

end)

button.default_events:on({"padding_left","padding_top"}, function (data, context)
    local props = context:all()
    if props.label then
        props.label:set({
                x = props.padding_left,
                y = props.padding_top,
            })
    end
end)

button.default_events:on("text", function (data, context)
    local props = context:all()
    if props.label then
        props.label:set("text", props.text)
        context:set({
                width = props.label:get("width") + props.padding_left + props.padding_right,
                height = props.label:get("height") + props.padding_bottom + props.padding_top
            })
    end
end)

button.default_events:on({"label", "rectangle"}, function (data, context)
    local props = context:all()
    local childs = context:get("children")

    if not props.label or not props.rectangle then
        return
    end

    if not childs:contains(props.label) or not childs:contains(props.rectangle) then
        childs:clear()

        if props.rectangle then
            childs:add(props.rectangle)
        end
        
        if props.label then
            childs:add(props.label)
        end
    end

    context.events:trigger("text", props.label:get("text"), context)
    props.rectangle.events:trigger("calc_size", data, context)
end)

button.default_events:on("rectangle", function (data, context)
    local props = context:all()
    if props.label then
        props.label:set("color", (props.rectangle and props.rectangle:get("border_color")) or props.color)
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