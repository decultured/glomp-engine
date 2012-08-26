local timer         = description.workon("glomp_time")
local window        = description.workon("glomp_window")
local theme_vals    = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()
local game_state    = description.workon("game_state")

local startup       = description.workon("startup_scene", "simple_gui_root")
startup:set({
        pct_width = 100,
        pct_height = 100,
    })

local title = description.workon("game_title", "simple_gui_label")
title:set({
        font = theme_vals.title_font,
        text = "Hey, Little Amoeba!",
        color = theme_vals.color,
        top = 50,
        left = 0,
        right = 0,
        align = "center"
    })

local go_bttn = description.workon("start_button", "simple_gui_button")
go_bttn:get("label"):set("font", theme_vals.title_font)
go_bttn:set({
        text = "Get Moving!",
        color = theme_vals.color,
        top = "50%",
        left = "50%",
        width = 500,
        height = 50,
        offset_x = 250
    })

tick(function ()
    print("lol")
end, 2)

go_bttn.events:on("click", function ()
    game_state:set("scene", game_state:get("game_scene"))
end)



startup:get("children"):add_many(title, go_bttn)

window:set("clear_color", theme_vals.main_bg_color)

window.events:on("update", function (data, context)
    -- startup:set("x", startup:get("x") + timer:get("frame_time") * 100)
    -- print(startup:get("x"))
end)