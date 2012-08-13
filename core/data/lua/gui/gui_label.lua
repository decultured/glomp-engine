glOMP = glOMP or {}
glOMP.gui = glOMP.gui or {}
 
local _g_graphics_print = glOMP.graphics.print
local _g_graphics_set_color = glOMP.graphics.set_color

local _label_base = {}

function _label_base:draw()
	if not self.text then
		return
	end

	if self.color then
		_g_graphics_set_color(hex_to_rgb(self.color))
	end
 
	if self.font then
		self.font:draw_string(self.text)
	else
		_g_graphics_print(self.text)
	end
end

glOMP.gui.Label = glOMP.View:extend(_label_base)
