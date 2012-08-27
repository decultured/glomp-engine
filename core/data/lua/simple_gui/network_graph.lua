local draw_line = glomp.graphics.line
local draw_fills = glomp.graphics.draw_fills
local draw_circle = glomp.graphics.circle
local random_color = random_color

local net_graph = definition.workon("simple_gui_network_graph", "simple_gui_element")

local net_node = definition.workon("simple_gui_network_node", "simple_gui_element")
net_node.defaults.radius    = 50
net_node.defaults.max_speed = 200
net_node.defaults.max_accel = 50
net_node.defaults.mass      = 1
net_node.defaults.vel_x     = 0
net_node.defaults.vel_y     = 0
net_node.defaults.f_x       = 0
net_node.defaults.f_y       = 0
net_node.defaults.force_x   = 0
net_node.defaults.force_y   = 0
net_node.defaults.num_links = 0
net_node.defaults.wants_input = false

net_node.default_events:on("draw", function (data, context)
    local props = context:all()

    -- print (props.parent, context.name)
    draw_fills(true)
    draw_circle(0, 0, props.radius or 100)
    draw_fills(false)
    draw_circle(0, 0, props.radius or 100)
end)

local net_link = definition.workon("simple_gui_network_link", "simple_gui_element")
net_link.defaults.left          = 0
net_link.defaults.top           = 0
net_link.defaults.source        = nil
net_link.defaults.destination   = nil
net_link.defaults.length        = 50
net_link.defaults.strength      = 20
net_link.defaults.wants_input   = false

net_link.default_events:on("draw", function (data, context)
    local props = context:all()
    if not props.source or not props.destination then
        return
    end

    local source_props = props.source:all()
    local dest_props = props.destination:all()

    draw_line(source_props.left, source_props.top, dest_props.left, dest_props.top)
end)

net_graph.defaults.nodes_container = nil
net_graph.defaults.links_container = nil
net_graph.defaults.nodes        = nil
net_graph.defaults.links        = nil
net_graph.defaults.draw_links   = false
net_graph.defaults.draw_nodes   = true
net_graph.defaults.gravity_spring           = true
net_graph.defaults.gravity_spring_length    = 250
net_graph.defaults.gravity_spring_strength  = 10
net_graph.defaults.gravity_spring_damping   = 0.5
net_graph.defaults.max_radius   = 10
net_graph.defaults.min_radius   = 5

net_graph.events:on("apply", function (data, context)
    local props = context:all()

    props.nodes_container = description.workon(context.name .. "_nodes_renderer", "simple_gui_element")
    props.nodes_container:set({
            pct_width = 100,
            pct_height = 100,
            x = 0,
            y = 0    
        })
    
    props.links_container = description.workon(context.name .. "_links_renderer", "simple_gui_element")
    props.links_container:set({
            pct_width = 100,
            pct_height = 100,
            x = 0,
            y = 0    
        })

    context:add_children(props.links_container, props.nodes_container)
end)

net_graph.default_events:on("update", function (data, context)
    local props = context:all()
    local times = data:all()

    if not props.visible then
        return false
    end

    props.nodes_container:set("visible", props.draw_nodes)
    props.links_container:set("visible", props.draw_links)

    local childs = props.nodes_container:get("children")
    if not childs then
        return
    end
    childs = childs.list
    local childs_len = #childs
    
    local links = props.links_container:get("children")
    if not links then
        return
    end
    links = links.list
    local links_len = #links
    
    local frame_time = times.frame_time

    local nodes_container   = props.nodes_container
    local links_container   = props.links_container
    local spring_len        = props.gravity_spring_length
    local damping           = props.gravity_spring_damping
    local spring_str        = -props.gravity_spring_strength

    -- first gravity
    local fp        = {}
    local sp        = {}
    local dist_sqd  = 0
    local dist      = 0
    local dir_x     = 0
    local dir_y     = 0
    local dir_xn    = 0
    local dir_yn    = 0
    local accel_mix = 0

    local i = 1
    while i < childs_len do
        local j = i + 1
        fp = childs[i].fields
        while j < childs_len + 1 do
            sp = childs[j].fields

            spring_len = (fp.radius + sp.radius) * 4

            dir_x = sp.left - fp.left
            dir_y = sp.top - fp.top

            dist_sqd = dir_x * dir_x + dir_y * dir_y
            dist = math.sqrt(dist_sqd)

            dir_xn = dir_x / dist
            dir_yn = dir_y / dist

            fp.f_x = fp.f_x + (-spring_str * (dist - spring_len) * dir_xn)
            fp.f_y = fp.f_y + (-spring_str * (dist - spring_len) * dir_yn)

            sp.f_x = sp.f_x + (-spring_str * (dist - spring_len) * -dir_xn)
            sp.f_y = sp.f_y + (-spring_str * (dist - spring_len) * -dir_yn)

            j = j + 1
        end
        i = i + 1
    end

    for i = 1, links_len do
        local link = links[i].fields
        fp = link.source.fields
        sp = link.destination.fields

        spring_len = (fp.radius + sp.radius) * 0.25
        spring_str = -link.strength

        dir_x = sp.left - fp.left
        dir_y = sp.top - fp.top

        dist_sqd = dir_x * dir_x + dir_y * dir_y
        dist = math.sqrt(dist_sqd)

        dir_xn = dir_x / dist
        dir_yn = dir_y / dist

        fp.f_x = fp.f_x + (-spring_str * (dist - spring_len) * dir_xn)
        fp.f_y = fp.f_y + (-spring_str * (dist - spring_len) * dir_yn)

        sp.f_x = sp.f_x + (-spring_str * (dist - spring_len) * -dir_xn)
        sp.f_y = sp.f_y + (-spring_str * (dist - spring_len) * -dir_yn)
    end

    -- then fix speeds, calc displacements
    for i = 1, childs_len do
        fp = childs[i].fields

        local accel_x = fp.f_x / fp.mass
        local accel_y = fp.f_y / fp.mass

        fp.f_x = 0
        fp.f_y = 0

        fp.vel_x = (fp.vel_x + frame_time * accel_x * 0.5) - fp.vel_x * damping * frame_time
        fp.vel_y = (fp.vel_y + frame_time * accel_y * 0.5) - fp.vel_y * damping * frame_time

        local speed = math.sqrt((fp.vel_x * fp.vel_x) + (fp.vel_y * fp.vel_y))

        if speed > fp.max_speed then
            fp.vel_x = (fp.vel_x / speed) * fp.max_speed
            fp.vel_y = (fp.vel_y / speed) * fp.max_speed
        end

        fp.left = fp.left + fp.vel_x * frame_time
        fp.top = fp.top + fp.vel_y * frame_time
    end
end)
local function node_dist_sorter(node1, node2)
    return node1:get("temp_dist") < node2:get("temp_dist")
end

local distance_squared = distance_squared

net_graph.methods.find_nearest_to_point = function(self, x, y, num)
    num = num or 1
    local props = self:all()
    local childs = props.nodes_container:get("children")
    if not childs then
        return
    end
    childs = childs.list
    local childs_len = #childs

    x = x + props.offset_x - props.world_x
    y = y + props.offset_y - props.world_y

    local list = {}

    for i = 1, childs_len do
        fp = childs[i].fields
        fp.temp_dist = distance_squared(x, y, fp.left, fp.top)
        if #list < num then
            table.insert(list, childs[i])
        else
            table.sort(list, node_dist_sorter)

            if fp.temp_dist < list[#list]:get("temp_dist") then
                list[#list] = childs[i]
            end
        end
    end
    table.sort(list, node_dist_sorter)
    return list
end

function populate_random_net_graph(graph, num_nodes, num_links, tree_parenting, random_parenting)
    local props = graph:all()
    local nodes = props.nodes_container
    local links = props.links_container

    links:clear_children()
    nodes:clear_children()

    for i = 1, num_nodes do
        local new_node = description.workon(graph.name .. "_node_" .. i, "simple_gui_network_node")
        new_node:set({
            left    = math.random() * (props.parent_width or props.width or 1000),
            top     = math.random() * (props.parent_height or props.height or 1000),
            radius  = (math.random() * (props.max_radius - props.min_radius)) + props.min_radius,
            color   = random_color_from_base(0, 100, 0, 70, 155, 70)
        })

        nodes:add_child(new_node)

        local children = nodes:get("children")
        if tree_parenting and i > 1 then
            local new_link = description.workon(graph.name .. "_link_" .. i, "simple_gui_network_link")

            local source_id = math.random(i - 1)

            new_link:set({
                source = children:get(source_id),
                destination = new_node
            })

            links:add_child(new_link)
        end
    end

    if random_parenting then
        return
    end

    for i = 1, num_links do
        local source_id = math.random(num_nodes)
        local dest_id = math.random(num_nodes)

        if source_id == dest_id then
            if source_id > 1 then
                source_id = source_id - 1
            elseif source_id == 1 then
                source_id = source_id + 1
            end
        end

        local new_link = description.workon(graph.name .. "_node_" .. i, "simple_gui_network_link")
        new_link:set({
            source = nodes:get(source_id),
            destination = nodes:get(dest_id)
        })

        links:add_child(new_link)
    end
end


net_graph.methods.point_in_node = function(self, x, y, tollerance)
    tollerance = tollerance or 0

    local childs = self:get("nodes_container"):get("children")
    if not childs then
        return
    end
    return childs:find(function (child)
        local props = child:all()
        local dist = distance_squared(x, y, props.left, props.top)
        
        if dist < (props.radius + tollerance) * (props.radius + tollerance) then
            return child
        end
    end)
end

net_graph.methods.remove_node = function(self, node)
    local props = self:all()
    local nodes = props.nodes_container
    local links = props.links_container

    nodes:remove_child(node)

    local childs = links:get("children")

    childs:clear()

    local filtered = links:filter_children(function(link) 
        if link:get("source") == node or link:get("destination") == node then
            return false
        else
            return link
        end
    end)
    if filtered then
        childs:add_many(unpack(filtered))
    end
end