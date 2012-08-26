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
        bottom = 20,
        left = 0,
        right = 0,
        align = "center"
    })

local go_bttn = description.workon("quit_button", "simple_gui_button")
go_bttn:set({
        text = "I quit",
        color = theme_vals.color,
        top = "50%",
        left = "50%",
        width = 500,
        height = 50,
        offset_x = 250
    })

go_bttn.events:on("click", function ()
    game_state:set("scene", game_state:get("startup_scene"))
end)

go_bttn:get("label"):set("font", theme_vals.title_font)

game_scene:get("children"):add_many(title, go_bttn)

game_scene.events:on("visible", function (data, context)
    print("gogogogogog", data)
end)