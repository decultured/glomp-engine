local mouse = description.workon("glomp_mouse")
local game_scene = description.workon("game_scene", "simple_gui_root")
local game_world = description.workon("game_world", "simple_gui_element")
local food_container = description.workon("food_container", "simple_gui_element")
local hurts_container = description.workon("hurts_container", "simple_gui_element")
local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

game_world:set({
        width = 1000,
        height = 1000,
        pressed = 0,
        food_speed = 20,
        food_decay = 3,
        hurt_speed = 20,
        hurt_decay = 3,
        max_food = 100,
        food_tollerance = 5
    })

local sprite_image = glomp.image.load("assets/images/spritesheet.png")
local sprite_test = description.workon("spritetest", "simple_gui_tile_map")

sprite_test:set({
        image = sprite_image,
        frames_wide = 4,
        frames_high = 4,
        top = 0,
        left = 0,
        offset_x = 0,
    })

local graph = description.workon("netgraph_test", "simple_gui_network_graph")
graph:set({
        top = 0,
        left = 0,
        right = 0,
        bottom = 0
    })

mouse.events:on("pressed", function ()
    game_world:set("pressed", true)
end)

mouse.events:on("released", function ()
    game_world:set("pressed", false)
end)

local magnitude = 5000
game_world.events:on("update", function (timer)
    local frame_time = timer:get("frame_time")
    if game_world:get("pressed") then
        local mouse_x = mouse:get("x")
        local mouse_y = mouse:get("y")
        local list = graph:find_nearest_to_point(mouse_x, mouse_y, 4)
        if list then
            for i = 1, #list do
                local node = list[i].fields
                local dx = mouse_x - node.left
                local dy = mouse_y - node.top
                local dist = math.sqrt(dx*dx + dy*dy)
                dx = (dx / dist) * magnitude
                dy = (dy / dist) * magnitude

                node.vel_x = node.vel_x + dx * frame_time
                node.vel_y = node.vel_y + dy * frame_time
            end
        end
    end

    food_container:each_children(function (child)
        if not child:get("visible") then
            return
        end

        if graph:point_in_node(child:get("x"), child:get("y"), game_world:get("food_tollerance")) then
            child:set("visible", false)
            theme_vals.phazer_sound:play()
        end
    end)

    hurts_container:each_children(function (child)
        if not child:get("visible") then
            return
        end

        local node = graph:point_in_node(child:get("x"), child:get("y"), game_world:get("food_tollerance"))

        if node then
            child:set("visible", false)
            graph:remove_node(node)
            theme_vals.quit_sound:play()
        end
    end)

end)

function adjust_food()
    local current = food_container:num_children()
    local more = game_world:get("max_food") - current

    if more < 1 then
        return current
    end
    
    for i = current + 1, current + more do
        local food = description.workon("game_food_" .. i, "game_food")
        food:set("visible", false)

        food_container:add_child(food)
    end
end

function adjust_hurts()
    local current = hurts_container:num_children()
    local more = game_world:get("max_food") - current

    if more < 1 then
        return current
    end
    
    for i = current + 1, current + more do
        local food = description.workon("game_hurt_" .. i, "game_food")
        food:set("visible", false)

        hurts_container:add_child(food)
    end
end

local function make_food()
    adjust_food()
    local foods = food_container:get("children")
    if math.random(100) < game_world:get("food_speed") then
        print ("fooding!")
        foods:find(function (food)
            if food:get("visible") then
                return false
            end
            food:set({
                color       = random_color_from_base(100, 100, 0, 70, 155, 70),
                border_color = random_color_from_base(100, 100, 0, 70, 155, 70),
                width       = math.random(10, 20),
                height      = math.random(10, 20),
                rotation    = math.random(20) - 10,
                x = math.random(game_world:get("width")),
                y = math.random(game_world:get("height")),
                visible = true
            })
            return true
        end)
    end

    if math.random(100) < game_world:get("food_decay") then
        print ("unfooding!")
        foods:find(function (food)
            if not food:get("visible") then
                return false
            else
                food:set("visible", false)
            end
        end)
    end
end


local function make_hurts()
    adjust_hurts()
    local foods = hurts_container:get("children")
    if math.random(100) < game_world:get("food_speed") then
        print ("hurting!")
        foods:find(function (food)
            if food:get("visible") then
                return false
            end
            food:set({
                color       = random_color_from_base(100, 0, 0, 70, 155, 70),
                border_color = random_color_from_base(100, 0, 0, 70, 155, 70),
                width       = math.random(10, 20),
                height      = math.random(10, 20),
                rotation    = math.random(20) - 10,
                x = math.random(game_world:get("width")),
                y = math.random(game_world:get("height")),
                visible = true
            })
            return true
        end)
    end

    if math.random(100) < game_world:get("food_decay") then
        print ("unhurting!")
        foods:find(function (food)
            if not food:get("visible") then
                return false
            else
                food:set("visible", false)
            end
        end)
    end
end


tick(make_food, 0.1)
tick(make_hurts, 0.2)



game_world:add_children(graph, food_container, hurts_container)

populate_random_net_graph(graph, 30, 20, true, true)


