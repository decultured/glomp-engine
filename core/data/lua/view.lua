glomp = glomp or {}
local table_utils = table_utils

view = view or {}
store = store or {}
store.views = store.views or {}

local views = store.views

function view:build_transforms()
	if self.parent and self.parent.matrix then
		self.matrix:copy_of(self.parent.matrix)
	else
		self.matrix:identity()
	end

	self.matrix:transform(self.x, self.y)
	self.matrix:rotate(self.rotation)
	self.matrix:scale(self.scale_x, self.scale_y)

	table_utils.each(self.sub_children, function(v)
		v:build_transforms()
	end)

	table_utils.each(self.children, function(v)
		v:build_transforms()
	end)
end

function view:trigger_bottom_up(event, ...)
	if not self.enabled then
		return
	end

	table_utils.each(self.sub_children, function(v, k, ...)
		v:trigger_bottom_up(event, ...)
	end)

	self.event_pump:trigger(event, self, ...)

	table_utils.each(self.children, function(v, k, ...)
		v:trigger_bottom_up(event, ...)
	end)
end

function view:trigger_top_down(event, ...)
	if not self.enabled then
		return
	end

	table_utils.each(self.sub_children, function(v, k, ...)
		v:trigger_top_down(event, ...)
	end)

	self.event_pump:trigger(event, self, ...)

	table_utils.each(self.children, function(v, k, ...)
		v:trigger_top_down(event, ...)
	end)
end

function view:add_child(child)
	if child.parent then
		child.parent:remove_sub_child(child)
		child.parent:remove_child(child)
	end

	child.parent = self
	table.insert(self.children, child)
	child:build_transforms()
end

function view:add_sub_child(child)
	if child.parent then
		child.parent:remove_sub_child(child)
		child.parent:remove_child(child)
	end

	child.parent = self
	table.insert(self.sub_children, child)
	child:build_transforms()
end

function view:remove_child(child)
	child.parent = nil
	table_utils.remove_one(self.children, child)
end

function view:remove_sub_child(child)
	child.parent = nil
	table_utils.remove_one(self.sub_children, child)
end

function view:initialize()

end

function view:draw()

end

function view:move(x, y)
	self.x = self.x + x
	self.y = self.y + y

	self:build_transforms(self.parent)
end

function view:rotate(angle)
	self.angle = self.angle + angle

	self:build_transforms(self.parent)
end

function view:scale(scale_x, scale_y)
	self.scale_x = self.scale_x + x
	self.scale_y = self.scale_y + y

	self:build_transforms(self.parent)
end

function view:on(...)
	self.event_pump:on(...)
end

function view:off(...)
	self.event_pump:on(...)
end

view.x = 0
view.y = 0
view.rotation = 0
view.scale_x = 1.0
view.scale_y = 1.0
view.enabled = true
view.visible = true
view.parent = nil
view.event_pump = event_pump.load(name)

function view.workon(name, fields)
	local result = self:fetch(name, fields)
	if not result then
		result = self:create(name, fields)
	end
	return result
end

function view:fetch(name, fields)
	if not name then
		error ("View name must not be nil")
		return false
	end

	local found_view = views[name]

	if found_view then
		table_utils.extend_original(found_view, fields)
		return found_view
	end

	return false
end

function view:create(name, fields)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		fields = name
		name = UUID()
	end

	if views[name] then
		error ("Existing view found (Perhaps you want 'use'?): " .. name)
		return false
	end

	local new_view = self:extend({
				name = name,
				sub_children = {},
				children = {}
			})

	views[name] = new_view

	table_utils.extend_original(new_view, fields)

	new_view.matrix = matrix4x4.create()
	new_view.inv_matrix = matrix4x4.create()

	return new_view
end

function view:clone(name)
	if not name then
		name = UUID()
	end

	local new_view = table_utils.shallow_copy(self)
	new_view.event_pump = self.event_pump:clone(name)
	new_view.matrix = matrix4x4.create()
	new_view.inv_matrix = matrix4x4.create()

	return new_view
end

function view:extend(mixin, name)
	if not name then
		name = UUID()
	end

	local new_view = table_utils.extend(self, mixin)
	new_view.event_pump = self.event_pump:clone(name)
	return new_view
end