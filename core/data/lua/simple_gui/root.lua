local theme_vals = description.workon("simple_gui_active_theme", "simple_gui_theme"):all()

local root = definition.workon("simple_gui_root", "simple_gui_element")

root.defaults.width     = 800
root.defaults.height    = 600
root.defaults.x         = 0
root.defaults.y         = 0
root.defaults.scale_x   = 1
root.defaults.scale_y   = 1
