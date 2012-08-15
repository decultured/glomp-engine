glomp = glomp or {}
local _g_table_utils = glomp.table_utils
local _g_graphics = glomp.graphics

glomp.view = glomp.view or {}
glomp.store = glomp.store or {}
glomp.store.views = glomp.store.views or {}

local _g_views = glomp.store.views
local _g_view = glomp.view

function glomp.view:render( )
	_g_graphics.push_2d_transform(self.x, self.y, self.rotation, self.scale_x, self.scale_y)


	if self.visible then
		--self:draw()
	end


	_g_graphics.pop_matrix()
end

function glomp.view.trigger_bottom_up(event, ...)
	if not self.enabled then
		return
	end

	_g_table_utils.call_each(self.sub_children, event)

	self.event_pump:trigger(event, self)

	_g_table_utils.call_each(self.children, event)
end

function glomp.view.trigger_top_down(...)
	if not self.enabled then
		return
	end

	_g_table_utils.call_each(self.children, event)

	self.event_pump:trigger(event, self)

	_g_table_utils.call_each(self.sub_children, event)
end

function glomp.view:add_child(view)
	table.insert(self.children, view)
end

function glomp.view:add_sub_child(view)
	table.insert(self.sub_children, view)
end

function glomp.view:remove_child(view)
	_g_table_utils.remove_one(self.children, view)
end

function glomp.view:remove_sub_child(view)
	_g_table_utils.remove_one(self.sub_children, view)
end

function glomp.view:initialize()

end

function glomp.view:draw()

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
glomp.view.event_pump = glomp.event_pump.load(name)

function glomp.view:fetch_or_create(name, attributes)
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
		error ("Existing view found (Perhaps you want 'fetch_or_create'?): " .. name)
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