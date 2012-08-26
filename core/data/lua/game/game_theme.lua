if not definition.fetch("simple_gui_theme") then
    load_module("simple_gui/theme_def")
end

local theme = description.workon("simple_gui_active_theme", "simple_gui_theme")

local base_theme = theme:all()

local theme_vals = {}

theme_vals.main_color       = base_theme.white
theme_vals.main_bg_color    = base_theme.green
theme_vals.font             = nil
theme_vals.title_font       = glomp.font.load("assets/fonts/Eater-Regular.ttf", 45, true, false, true, 0.9, 100)

theme:set(theme_vals)

