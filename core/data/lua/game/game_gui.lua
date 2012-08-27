local game_scene    = description.workon("game_scene", "simple_gui_root")
local game_gui      = description.workon("game_gui", "simple_gui_root")
local game_state    = description.workon("game_state")
local theme_vals    = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

game_gui:set({
        pct_width = 100,
        pct_height = 100,
    })

local title = description.workon("somejunks", "simple_gui_label")
title:set({
        font = theme_vals.sub_title_font,
        text = "Eat the green things, avoid the red things.",
        color = theme_vals.color,
        top = 10,
        bottom = 0,
        left = 0,
        right = 0,
        align = "center",
        v_align = "top"
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

game_gui:add_children(title, go_bttn)