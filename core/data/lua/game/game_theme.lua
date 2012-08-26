if not definition.fetch("simple_gui_theme") then
    load_module("simple_gui/theme_def")
end

local theme = description.workon("simple_gui_active_theme", "simple_gui_theme")

local base_theme = theme:all()

local theme_vals = {}

theme_vals.main_color       = base_theme.white
theme_vals.main_bg_color    = base_theme.off_black
theme_vals.font             = nil
theme_vals.title_font       = glomp.font.load("assets/fonts/CabinSketch-Bold.ttf", 64, true, false, true, 0.9, 100)
theme_vals.sub_title_font   = glomp.font.load("assets/fonts/CabinSketch-Regular.ttf", 26, true, false, true, 0.9, 100)
theme_vals.gui_font         = glomp.font.load("assets/fonts/NovaOval.ttf", 18, true, false, true, 0.9, 100)
theme_vals.tiny_font        = glomp.font.load("assets/fonts/Cousine-Bold.ttf", 8, true, false, true, 0.9, 100)
theme_vals.phazer_sound     = glomp.sound.load("assets/sounds/phazer.ogg")
theme_vals.quit_sound       = glomp.sound.load("assets/sounds/outs.ogg")
theme_vals.ambient_sound_1  = glomp.sound.load("assets/sounds/ambient1.ogg")


theme:set(theme_vals)

