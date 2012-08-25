local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local label = definition.workon("simple_gui_label", "simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate
local set_color_hex     = glomp.graphics.set_color_hex
local print_string      = glomp.graphics.print

label.defaults.color         = theme_vals.main_color
label.defaults.text          = "nothing."
label.defaults.display_text  = "nothing."
label.defaults.multi_line    = false
label.defaults.wrap          = false
label.defaults.max_width     = nil
label.defaults.font          = nil
label.defaults.is_monospaced = true

label.default_events:on("text", function (data, context)
        local props = context:all()

        -- calculate width, height
        props.display_text = props.text
    end)

label.default_events:on("font", function (data, context)
        -- calculate width, height
    end)

label.default_events:on("draw", function (data, context)
        props = context:all()

        if not props.visible then
            return
        end

        if not props.display_text and props.text then
            context.events:trigger("text", props.text, context)
        end

        push_matrix()
        translate(props.x, props.y)

        set_color_hex(props.color)
        if props.font then
            props.font:draw_string(props.display_text)
        else
            print_string(props.display_text)
        end

        props.children:trigger_all("draw", context)

        pop_matrix()
    end)
