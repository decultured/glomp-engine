glomp = glomp or {}
glomp.gui = glomp.gui or {}
 
local function draw_image(props)
	glomp.graphics.set_color(255, 255, 255)
	if props.image then
		props.image:draw()
	end
end

glomp.gui.image = glomp.view:clone("gui_image")
glomp.gui.image.draw = draw_image
glomp.gui.image:on("draw", draw_image)
