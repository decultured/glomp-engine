glOMP = glOMP or {}
glOMP.gui = glOMP.gui or {}
 
local _image_base = {}

function _image_base:draw()
	if self.image then
		self.image:draw()
	end

	self.rotation = self.rotation + 0.9
end

glOMP.gui.Image = glOMP.View:extend(_image_base)
