glomp = glomp or {}
glomp.gui = glomp.gui or {}
 
local _g_graphics_print = glomp.graphics.print
local _g_graphics_set_color = glomp.graphics.set_color

local function draw_label(props)
	if not props.text then
		return
	end

	if props.color then
		_g_graphics_set_color(hex_to_rgb(props.color))
	end
 
	if props.font then
		props.font:draw_string(props.text)
	else
		_g_graphics_print(props.text)
	end
end

glomp.gui.label = glomp.view:clone("gui_label")
glomp.gui.label.draw = draw_label
glomp.gui.label:on("draw", draw_label)