local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local label = definition.workon("simple_gui_label", "simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate
local set_color_hex     = glomp.graphics.set_color_hex
local print_string      = glomp.graphics.print

label.defaults.color            = theme_vals.main_color
label.defaults.text             = "nothing."
label.defaults.display_text     = "nothing."
label.defaults.multi_line       = false
label.defaults.num_lines        = 1
label.defaults.wrap             = false
label.defaults.max_width        = nil
label.defaults.font             = nil
label.defaults.is_monospaced    = true
label.defaults.font_height      = 8
label.defaults.align            = "center"
label.defaults.v_align          = "middle"
label.defaults.text_height      = 0
label.defaults.text_width       = 0
label.defaults.text_offset_x    = 0
label.defaults.text_offset_y    = 0

label.default_events:on("text", function (data, context)
        local props = context:all()
        local font = props.font

        local text_height = 0
        local text_width = 0

        -- GLUT_BITMAP_8_BY_13
        if not font then
            text_height = 8
            text_width  = string.len(data) * 8
        else
            text_height = font:get_string_height(data)
            text_width  = font:get_string_width(data)
        end

        context:set({
                text_height = text_height,
                text_width = text_width,
                display_text = data
            })

        context.events:trigger("align", props.align, context)
    end)

label.default_events:on({"parent_width", "width", "align", "text_width"}, function (data, context)
    local props = context:all()

    if not props.align then
        return
    end

    if props.align == "right" then
        context:set("text_offset_x", props.width - props.text_width)
    elseif props.align == "center" then
        context:set("text_offset_x", (props.width - props.text_width) * 0.5)
    else
        context:set("text_offset_x", 0)
    end
end)

label.default_events:on({"parent_height", "height", "v_align", "text_height"}, function (data, context)
    local props = context:all()

    if not props.v_align then
        return
    end

    if props.v_align == "bottom" then
        context:set("text_offset_y", props.height - props.text_height)
    elseif props.v_align == "middle" then
        context:set("text_offset_y", (props.height - props.text_height) * 0.5)
    else
        context:set("text_offset_y", 0)
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

        -- if not props.display_text and props.text then
            context.events:trigger("text", props.text, context)
        -- end

        push_matrix()
        translate(props.text_offset_x, props.font_height + props.text_offset_y)
        if props.font then
            props.font:draw_string(props.display_text)
        else
            print_string(props.display_text)
        end
        pop_matrix()
    end)
