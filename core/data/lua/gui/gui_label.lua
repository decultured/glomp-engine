glomp = glomp or {}
glomp.gui = glomp.gui or {}
 
local _g_graphics_print = glomp.graphics.print
local _g_graphics_set_color = glomp.graphics.set_color

local function draw_label(view)
	if not view.text then
		return
	end

	if view.color then
		_g_graphics_set_color(hex_to_rgb(view.color))
	end
 
	view.matrix:push()

	if view.font then
		view.font:draw_string(view.text)
	else
		_g_graphics_print(view.text)
	end

	view.matrix:pop()
end

glomp.gui.label = glomp.view:clone("gui_label")
glomp.gui.label.draw = draw_label
glomp.gui.label:on("draw", draw_label)