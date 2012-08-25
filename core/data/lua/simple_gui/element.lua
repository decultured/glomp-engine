local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local gui_element = definition.workon("simple_gui_element")

local push_matrix       = glomp.graphics.push_matrix
local pop_matrix        = glomp.graphics.pop_matrix
local translate         = glomp.graphics.translate
local scale             = glomp.graphics.scale
local set_color_hex     = glomp.graphics.set_color_hex

gui_element.defaults.parent     = nil

gui_element.parent_width        = 100
gui_element.parent_height       = 100

gui_element.defaults.x          = 0
gui_element.defaults.y          = 0
gui_element.defaults.width      = 100
gui_element.defaults.height     = 100
gui_element.defaults.pct_width  = nil
gui_element.defaults.pct_height = nil
gui_element.defaults.top        = nil
gui_element.defaults.left       = nil
gui_element.defaults.right      = nil
gui_element.defaults.bottom     = nil
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
                local old_parent_childs = old_parent and old_parent:get("children")
                if old_parent_childs then
                    old_parent_childs:remove(new_child)
                end
            end

            new_child:set({
                    parent = context.name,
                    parent_width = context:get("width"),
                    parent_height = context:get("height"),
                })

            context.events:trigger("changed", data, context)
        end)

    children.events:on("remove", function (new_child)
            new_child:unset("parent")
            new_child:unset("parent_width")
            new_child:unset("parent_height")
        end)

end)

gui_element.default_events:on("render", function (data, context)
    local props = context:all()
    if not props.visible then
        return
    end

    context.events:trigger("transform", data, context)

    set_color_hex(props.color)

    context.events:trigger("draw", data, context)
    props.children:trigger_all("render", context)
    context.events:trigger("un_transform", data, context)
end)


gui_element.default_events:on("transform", function (data, context)
        local props = context:all()

        push_matrix()
        translate(props.x, props.y)
        if (props.scale_x and props.scale_x ~= 1) or
            (props.scale_y and props.scale_y ~= 1) then
            scale(props.scale_x, props.scale_y)
        end
end)

gui_element.default_events:on("un_transform", function (data, context)
        pop_matrix()
end)

local pct_num = percent_string_to_num

gui_element.default_events:on("changed", function (data, context)
        local props = context:all()
        local new_vals = {}

        new_vals.x = pct_num(props.left, props.parent_width) or props.left or props.x or 0
        new_vals.y = pct_num(props.top, props.parent_height) or props.top or props.y or 0
        
        -- print (context.name, new_vals, props.parent_width, props.parent_height, props.parent)

        if not props.parent_width or not props.parent_height then
            props.children:trigger_all("parent_transform", new_vals, context)
            context:set(new_vals)
            return
        end

        if props.pct_width then
            new_vals.width = pct_num(props.pct_width, props.parent_width) or (tonumber(props.pct_width) and tonumber(props.pct_width) * props.parent_width)
        elseif props.right then
            new_vals.width = pct_num(props.right, props.parent_width) or props.parent_width - props.right - props.x
        end

        new_vals.width = new_vals.width or props.width or 100 
        new_vals.width = math.max(new_vals.width, 0)
        new_vals.width = math.min(new_vals.width, props.parent_width)

        if props.pct_height then
            new_vals.height = pct_num(props.pct_height, props.parent_height) or props.pct_height * props.parent_height
        elseif props.bottom then
            new_vals.height = pct_num(props.bottom, props.parent_height) or props.parent_height - props.bottom - props.y
        end

        new_vals.height = new_vals.height or props.height or 0
        new_vals.height = math.max(new_vals.height, 0)
        new_vals.height = math.min(new_vals.height, props.parent_height)

        props.children:trigger_all("parent_transform", new_vals, context)

        context:set(new_vals)
end)

gui_element.default_events:on("parent_transform", function(data, context)
        if data.width then
            context:set("parent_width", data.width)
        end

        if data.height then
            context:set("parent_height", data.height)
        end
    end)

gui_element.default_events:on("test_mouse_down", function (data, context)
        local mouse_props = data:all()
        local props = context:all()
        
        if props.children:reverse_trigger_all_until("test_mouse_down", data) then
            return true
        end

        if props.hover and point_in_rect(mouse_props.x, mouse_props.y, props.x, props.y, props.width, props.height) then
            context:set("mouse_down", true)
            return true
        end
    end)

gui_element.default_events:on("test_mouse_over", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        if props.children:reverse_trigger_all_until("test_mouse_over", data) then
            return true
        end

        if props.hover then
            return true
        end

        if point_in_rect(mouse_props.x, mouse_props.y, props.x, props.y, props.width, props.height) then
            data_store:each("definition_index:".."simple_gui_element", function (item, index)
                    if item.fields.hover then
                        item:set("hover", false)
                        item.events:trigger("mouse_out", data, context)
                    end
                end)
            context:set("hover", true)
            context.events:trigger("mouse_over", data, context)
            return true
        end
    end)

gui_element.default_events:on("test_mouse_out", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        props.children:reverse_trigger_all("test_mouse_out", data)

        if props.hover and point_in_rect(mouse_props.x, mouse_props.y, props.x, props.y, props.width, props.height) then
            context:set("hover", false)
            context.events:trigger("mouse_out", data, context)
        end
    end)

gui_element.default_events:on("test_mouse_dragged", function (data, context)
        local mouse_props = data:all()
        local props = context:all()

        if props.mouse_down then
            context.events:trigger("mouse_dragged", data, context)
            print ("Dragging:", mouse_props.x, mouse_props.y)
        end
    end)