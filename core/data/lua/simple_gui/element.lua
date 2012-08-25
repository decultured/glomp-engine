local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local gui_element = definition.workon("simple_gui_element")

local draw_fills        = glomp.graphics.draw_fills
local draw_rectangle    = glomp.graphics.rectangle
local set_color_hex     = glomp.graphics.set_color_hex
local set_line_width    = glomp.graphics.set_line_width

gui_element.defaults.parent     = nil
gui_element.defaults.x          = 0
gui_element.defaults.y          = 0
gui_element.defaults.width      = 100
gui_element.defaults.height     = 100
gui_element.defaults.color      = theme_vals.main_color
gui_element.defaults.visible    = true
gui_element.defaults.hover      = false

gui_element.events:on("apply", function(data, context)
        local children = collection.workon(context.name .. "_children", "simple_gui_element")
        context:set("children", children)

        children.events:on("add", function (new_child)
                local old_parent_name = new_child:get("parent")
                if old_parent_name then
                    local old_parent = description.fetch(old_parent_name)
                    local old_parent_childs = old_parent:get("children")
                    if old_parent_childs then
                        old_parent_childs:remove(new_child)
                    end
                end

                new_child:set("parent", context.name)
            end)

        children.events:on("remove", function (new_child)
                new_child:unset("parent")
            end)
    end)

gui_element.default_events:on("test_mouse_down", function (data, context)
        local mouse_props = data:all()
        local props = context:all()
        
        if mouse_props.x < props.x + props.width and mouse_props.x > props.x and
            mouse_props.y < props.y + props.height and mouse_props.y > props.y then
            context.events:trigger("mouse_down", data, context)
            return true
        end
    end)

gui_element.default_events:on("test_mouse_up", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        if mouse_props.x < props.x + props.width and mouse_props.x > props.x and
            mouse_props.y < props.y + props.height and mouse_props.y > props.y then
            context.events:trigger("mouse_up", data, context)
        end
    end)

gui_element.default_events:on("test_mouse_moved", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        if mouse_props.x < props.x + props.width and mouse_props.x > props.x and
            mouse_props.y < props.y + props.height and mouse_props.y > props.y then

            if not props.hover then
                context:set("hover", true)
                context.events:trigger("mouse_over", data, context)
            end
        elseif props.hover then
            context:set("hover", false)
            context.events:trigger("mouse_out", data, context)
        end

        props.children:trigger_all("test_mouse_moved", data)
    end)

gui_element.default_events:on("test_mouse_dragged", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        if mouse_props.x < props.x + props.width and mouse_props.x > props.x and
            mouse_props.y < props.y + props.height and mouse_props.y > props.y then
            context.events:trigger("mouse_dragged", data, context)
        end
    end)