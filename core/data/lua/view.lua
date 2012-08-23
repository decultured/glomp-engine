glomp = glomp or {}
local _g_table_utils = glomp.table_utils
local _g_graphics = glomp.graphics

glomp.view = glomp.view or {}
glomp.store = glomp.store or {}
glomp.store.views = glomp.store.views or {}

local _g_views = glomp.store.views
local _g_view = glomp.view

function glomp.view:build_transforms()
	if self.parent and self.parent.matrix then
		self.matrix:copy_of(self.parent.matrix)
	else
		self.matrix:identity()
	end

	self.matrix:transform(self.x, self.y)
	self.matrix:rotate(self.rotation)
	self.matrix:scale(self.scale_x, self.scale_y)

	_g_table_utils.each(self.sub_children, function(v)
		v:build_transforms()
	end)

	_g_table_utils.each(self.children, function(v)
		v:build_transforms()
	end)
end

function glomp.view:trigger_bottom_up(event, ...)
	if not self.enabled then
		return
	end

	_g_table_utils.each(self.sub_children, function(v, k, ...)
		v:trigger_bottom_up(event, ...)
	end)

	self.event_pump:trigger(event, self, ...)

	_g_table_utils.each(self.children, function(v, k, ...)
		v:trigger_bottom_up(event, ...)
	end)
end

function glomp.view:trigger_top_down(event, ...)
	if not self.enabled then
		return
	end

	_g_table_utils.each(self.sub_children, function(v, k, ...)
		v:trigger_top_down(event, ...)
	end)

	self.event_pump:trigger(event, self, ...)

	_g_table_utils.each(self.children, function(v, k, ...)
		v:trigger_top_down(event, ...)
	end)
end

function glomp.view:add_child(child)
	if child.parent then
		child.parent:remove_sub_child(child)
		child.parent:remove_child(child)
	end

	child.parent = self
	table.insert(self.children, child)
	child:build_transforms()
end

function glomp.view:add_sub_child(child)
	if child.parent then
		child.parent:remove_sub_child(child)
		child.parent:remove_child(child)
	end

	child.parent = self
	table.insert(self.sub_children, child)
	child:build_transforms()
end

function glomp.view:remove_child(child)
	child.parent = nil
	_g_table_utils.remove_one(self.children, child)
end

function glomp.view:remove_sub_child(child)
	child.parent = nil
	_g_table_utils.remove_one(self.sub_children, child)
end

function glomp.view:initialize()

end

function glomp.view:draw()

end

function glomp.view:move(x, y)
	self.x = self.x + x
	self.y = self.y + y

	self:build_transforms(self.parent)
end

function glomp.view:rotate(angle)
	self.angle = self.angle + angle

	self:build_transforms(self.parent)
end

function glomp.view:scale(scale_x, scale_y)
	self.scale_x = self.scale_x + x
	self.scale_y = self.scale_y + y

	self:build_transforms(self.parent)
end

function glomp.view:on(...)
	self.event_pump:on(...)
end

function glomp.view:off(...)
	self.event_pump:on(...)
end

glomp.view.x = 0
glomp.view.y = 0
glomp.view.rotation = 0
glomp.view.scale_x = 1.0
glomp.view.scale_y = 1.0
glomp.view.enabled = true
glomp.view.visible = true
glomp.view.parent = nil
glomp.view.event_pump = glomp.event_pump.load(name)

function glomp.view.workon(name, attributes)
	local result = self:fetch(name, attributes)
	if not result then
		result = self:create(name, attributes)
	end
	return result
end

function glomp.view:fetch(name, attributes)
	if not name then
		error ("View name must not be nil")
		return false
	end

	local found_view = _g_views[name]

	if found_view then
		_g_table_utils.extend_original(found_view, attributes)
		return found_view
	end

	return false
end

function glomp.view:create(name, attributes)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		attributes = name
		name = UUID()
	end

	if _g_views[name] then
		error ("Existing view found (Perhaps you want 'use'?): " .. name)
		return false
	end

	local new_view = self:extend({
				name = name,
				sub_children = {},
				children = {}
			})

	_g_views[name] = new_view

	_g_table_utils.extend_original(new_view, attributes)

	new_view.matrix = glomp.matrix4x4.create()
	new_view.inv_matrix = glomp.matrix4x4.create()

	return new_view
end

function glomp.view:clone(name)
	if not name then
		name = UUID()
	end

	local new_view = _g_table_utils.shallow_copy(self)
	new_view.event_pump = self.event_pump:clone(name)
	new_view.matrix = glomp.matrix4x4.create()
	new_view.inv_matrix = glomp.matrix4x4.create()

	return new_view
end

function glomp.view:extend(mixin, name)
	if not name then
		name = UUID()
	end

	local new_view = _g_table_utils.extend(self, mixin)
	new_view.event_pump = self.event_pump:clone(name)
	return new_view
end