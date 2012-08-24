-- Default theme based on Solarized

local theme_def = definition.workon("simple_gui_theme")

local defaults = theme_def.defaults

defaults.black         = 0x002b36
defaults.off_black     = 0x073642

defaults.darker_gray   = 0x586e75
defaults.dark_gray     = 0x657b83
defaults.light_gray    = 0x839496
defaults.lighter_gray  = 0x93a1a1

defaults.off_white     = 0xeee8d5
defaults.white         = 0xfdf6e3

defaults.yellow        = 0xb58900
defaults.orange        = 0xcb4b16
defaults.red           = 0xdc322f
defaults.magenta       = 0xd33682
defaults.violet        = 0x6c71c4
defaults.blue          = 0x268bd2
defaults.cyan          = 0x2aa198
defaults.green         = 0x859900

defaults.component_bg       = defaults.lighter_gray
defaults.main_color         = defaults.off_black
defaults.main_bg_color      = defaults.white
defaults.highlight_color    = defaults.green
defaults.active_color       = defaults.yellow
defaults.disabled_color     = defaults.off_white

defaults.line_width = 2

