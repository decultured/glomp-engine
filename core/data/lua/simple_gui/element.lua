local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local gui_element = definition.workon("simple_gui_element")

local pct_num           = percent_string_to_num

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
gui_element.defaults.world_x    = 0
gui_element.defaults.world_y    = 0
gui_element.defaults.calc_x     = 0
gui_element.defaults.calc_y     = 0
gui_element.defaults.offset_x   = 0
gui_element.defaults.offset_y   = 0
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

gui_element.events:on("update", function (data, context)
    props.children:trigger_all("update", data)
end)

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

    if props.color then
        set_color_hex(props.color)
    end

    context.events:trigger("draw", data, context)
    props.children:trigger_all("render", context)
    context.events:trigger("un_transform", data, context)
end)


gui_element.default_events:on("transform", function (data, context)
        local props = context:all()

        push_matrix()
        context:calc_transforms()
        translate(props.x - props.offset_x, props.y - props.offset_y)
        if (props.scale_x and props.scale_x ~= 1) or
            (props.scale_y and props.scale_y ~= 1) then
            scale(props.scale_x, props.scale_y)
        end
end)

gui_element.default_events:on("un_transform", function (data, context)
        pop_matrix()
end)

gui_element.methods.local_point_inside = function (self, x, y)
    local props = self.fields
    local true_x = props.x - props.offset_x
    local true_y = props.y - props.offset_y

    return point_in_rect(x, y, true_x, true_y, props.width, props.height)
end

gui_element.methods.world_point_inside = function (self, x, y)
    local props = self.fields
    local true_x = props.world_x + props.x - props.offset_x
    local true_y = props.world_y + props.y - props.offset_y

    return point_in_rect(x, y, true_x, true_y, props.width, props.height)
end

gui_element.methods.calc_transforms = function (self)
        local props = self:all()
        local new_vals = {}

        new_vals.width = tonumber(props.width) or 0
        new_vals.height = tonumber(props.height) or 0
        new_vals.x = tonumber(props.x) or 0
        new_vals.y = tonumber(props.y) or 0

        new_vals.x = pct_num(props.left, props.parent_width) or tonumber(props.left) or props.x or 0
        new_vals.y = pct_num(props.top, props.parent_height) or tonumber(props.top) or props.y or 0
        
        if tonumber(props.pct_width) and props.parent_width then
            new_vals.width = pct_num(props.pct_width, props.parent_width) or props.pct_width * props.parent_width
        elseif props.right and props.parent_width then
            new_vals.width = pct_num(props.right, props.parent_width) or props.parent_width - props.right - new_vals.x
        end

        new_vals.width = new_vals.width or props.width or 100 
        new_vals.width = math.max(new_vals.width, 0)
        new_vals.width = math.min(new_vals.width, props.parent_width or math.huge)

        if tonumber(props.pct_height) and props.parent_height then
            new_vals.height = pct_num(props.pct_height, props.parent_height) or props.pct_height * props.parent_height
        elseif props.bottom and props.parent_height then
            new_vals.height = pct_num(props.bottom, props.parent_height) or props.parent_height - props.bottom - new_vals.y
        end

        new_vals.height = new_vals.height or props.height or 0
        new_vals.height = math.max(new_vals.height, 0)
        new_vals.height = math.min(new_vals.height, props.parent_height or math.huge)

        self:set(new_vals)

        props.children:each(function (child)
            child:set({
                    parent_width = props.width,
                    parent_height = props.height,
                    world_x = props.world_x + props.x,
                    world_y = props.world_y + props.y,
                })
            child:calc_transforms()
        end)
    end


gui_element.methods.test_mouse = function (self, mouse_props, pressed, released)
        local props = self:all()
        local found = false

        if not props.visible then
            return
        end

        props.children:each(function (child)
            found = child:test_mouse(mouse_props, pressed, released)
        end)

        local is_inside = self:world_point_inside(mouse_props:get("x"), mouse_props:get("y"))

        if props.mouse_down and released then
            self:set("mouse_down", false)
        elseif props.mouse_down then
            self.events:trigger("mouse_dragged", mouse_props, self)
        end

        if props.hover and (not is_inside or found) then
            self:set("hover", false)
            self.events:trigger("mouse_out", mouse_props, self)
        end

        if not found and is_inside then
            if not props.hover then
                self:set("hover", true)
                found = self.events:trigger("mouse_over", mouse_props, self)
            end

            if pressed then
                self:set("mouse_down", true)
            end

            if released then
                self.events:trigger("mouse_up", true, self)
            end
        end

        return found
    end
