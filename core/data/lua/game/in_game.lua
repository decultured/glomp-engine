local keyboard      = description.workon("glomp_keyboard")
local mouse         = description.workon("glomp_mouse")
local timer         = description.workon("glomp_time")
local window        = description.workon("glomp_window")
local theme_vals    = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()
local game_state    = description.workon("game_state")

local game_gui      = description.workon("game_gui", "simple_gui_root")
local game_world    = description.workon("game_world", "simple_gui_root")

local game_scene = description.workon("game_scene", "simple_gui_root")
game_scene:set({
        pct_width = 100,
        pct_height = 100,
    })

local horizontal_speed = 0
local vertical_speed = 0

keyboard.events:on("changed", function ()
    local speed = 1000
    horizontal_speed = 0
    if keyboard:get("LEFT", 0) > 0 then
        horizontal_speed = horizontal_speed + speed
    end
    if keyboard:get("RIGHT", 0) > 0 then
        horizontal_speed = horizontal_speed - speed
    end

    vertical_speed = 0
    if keyboard:get("UP", 0) > 0 then
        vertical_speed = vertical_speed + speed
    end
    if keyboard:get("DOWN", 0) > 0 then
        vertical_speed = vertical_speed - speed
    end
end)

window.events:on("update", function (data, context)
    
    -- game_world:add_to("x", horizontal_speed * timer:get("frame_time"))
    -- game_world:add_to("y", vertical_speed * timer:get("frame_time"))
end)

game_scene:add_children(game_world, game_gui)
