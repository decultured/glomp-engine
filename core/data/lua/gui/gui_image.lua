glomp = glomp or {}
glomp.gui = glomp.gui or {}
 
local function draw_image(view)
	view.matrix:push()

	glomp.graphics.set_color(255, 255, 255)
	if view.image then
		view.image:draw()
	end

	view.matrix:pop()
end

glomp.gui.image = glomp.view:clone("gui_image")
glomp.gui.image.draw = draw_image
glomp.gui.image:on("draw", draw_image)
