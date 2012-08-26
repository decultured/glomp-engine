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
        right = 0,
        align = "right",
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
local sprite_test = description.workon("spritetest", "simple_gui_sprite_sheet")

sprite_test:set({
        image = sprite_image,
        frames_wide = 5,
        frames_high = 6,
        x = 200,
        y = 300
    })

local map_test = glomp.image

function cycle_frames()
    local frame = sprite_test:get("current_frame") + 1
    if frame > sprite_test:get("frames_wide") * sprite_test:get("frames_high") then
        frame = 1
    end
    sprite_test:set("current_frame", frame)
end

tick(cycle_frames, 0.1)

game_scene:get("children"):add_many(title, go_bttn, sprite_test)
