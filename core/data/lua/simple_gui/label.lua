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
label.defaults.num_lines     = 1
label.defaults.wrap          = false
label.defaults.max_width     = nil
label.defaults.font          = nil
label.defaults.is_monospaced = true
label.defaults.font_height   = 8

label.default_events:on("text", function (data, context)
        local props = context:all()
        local font = props.font

        -- GLUT_BITMAP_8_BY_13
        if not font then
            context:set({
                    height = 8,
                    width = string.len(data) * 8,
                    display_text = data
                })
        else
            context:set({
                    height = font:get_string_height(data),
                    width = font:get_string_width(data),
                    display_text = data
                })
        end
    end)

label.default_events:on("font", function (data, context)
        context.events:trigger("text", context:get("text"), context)

        if data then
            context:set("font_height", data:get_string_height("M"))
        end
    end)

label.default_events:on("draw", function (data, context)
        props = context:all()

        if not props.display_text and props.text then
            context.events:trigger("text", props.text, context)
        end

        push_matrix()
        translate(0, props.font_height)
        if props.font then
            props.font:draw_string(props.display_text)
        else
            print_string(props.display_text)
        end
        pop_matrix()
    end)
