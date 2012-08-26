local keyboard      = description.workon("glomp_keyboard")
local mouse         = description.workon("glomp_mouse")
local timer         = description.workon("glomp_time")
local window        = description.workon("glomp_window")
local theme_vals    = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()
local game_state    = description.workon("game_state")

local game_scene = description.workon("game_scene", "simple_gui_root")
game_scene:set({
        pct_width = 100,
        pct_height = 100,
    })

local title = description.workon("somejunks", "simple_gui_label")
title:set({
        font = theme_vals.title_font,
        text = "WHAT NOW??!?!?!",
        color = theme_vals.color,
        top = 0,
        bottom = 0,
        left = 0,
        right = 0,
        align = "center",
        v_align = "middle"
    })

local go_bttn = description.workon("quit_button", "simple_gui_button")
go_bttn:get("label"):set("font", theme_vals.gui_font)
go_bttn:set({
        text = "I quit",
        color = theme_vals.color,
        bottom = 10,
        right = 10,
        width = 110,
        height = 40
    })

go_bttn.events:on("click", function ()
    game_state:set("scene", game_state:get("startup_scene"))
end)

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

local map_test = glomp.image

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

    print(keyboard:get("DOWN", 0))
end)

window.events:on("update", function (data, context)
    local props = sprite_test:all()
    sprite_test:add_to("left", horizontal_speed * timer:get("frame_time"))
    sprite_test:add_to("top", vertical_speed * timer:get("frame_time"))
end)

function cycle_frames()
    local frame = sprite_test:get("current_frame") + 1
    if frame > sprite_test:get("frames_wide") * sprite_test:get("frames_high") then
        frame = 1
    end
    sprite_test:set("current_frame", frame)
end

sprite_test:build_frames()


tick(cycle_frames, 0.4)

game_scene:get("children"):add_many(sprite_test, title, go_bttn)
