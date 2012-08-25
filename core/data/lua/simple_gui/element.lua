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

    end)

gui_element.default_events:on("test_mouse_up", function (data, context)

    end)

gui_element.default_events:on("test_mouse_moved", function (data, context)

    end)

gui_element.default_events:on("test_mouse_dragged", function (data, context)

    end)
