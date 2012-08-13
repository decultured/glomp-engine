glOMP = glOMP or {}
local _g_table_utils = glOMP.table_utils
local _g_graphics = glOMP.graphics

glOMP.View = glOMP.View or {}
glOMP.store = glOMP.store or {}
glOMP.store.views = glOMP.store.views or {}

local _g_views = glOMP.store.views
local _g_view = glOMP.View

function glOMP.View:render( )
	if not self.enabled then
		return
	end

	_g_graphics.push_2d_transform(self.x, self.y, self.rotation, self.scale_x, self.scale_y)

	_g_table_utils.call_each(self.sub_children, "render")

	if self.visible then
		self:draw()
	end

	_g_table_utils.call_each(self.children, "render")

	_g_graphics.pop_matrix()
end

function glOMP.View:add_child(view)
	table.insert(self.children, view)
end

function glOMP.View:add_sub_child(view)
	table.insert(self.sub_children, view)
end

function glOMP.View:remove_child(view)
	_g_table_utils.remove_one(self.children, view)
end

function glOMP.View:remove_sub_child(view)
	_g_table_utils.remove_one(self.sub_children, view)
end

function glOMP.View:initialize()

end

function glOMP.View:draw()

end

glOMP.View.x = 0
glOMP.View.y = 0
glOMP.View.rotation = 0
glOMP.View.scale_x = 1.0
glOMP.View.scale_y = 1.0
glOMP.View.enabled = true
glOMP.View.visible = true

function glOMP.View:get_or_create(name, defaults)
	local result = self:get(name, defaults)
	if not result then
		result = self:create(name, defaults)
	end
	return result
end

function glOMP.View:get(name, defaults)
	if not name then
		error ("View name must not be nil")
		return false
	end

	local found_view = _g_views[name]

	if found_view then
		_g_table_utils.set_defaults(found_view, defaults)
		return found_view
	end

	warning ("View not found: ".. name)

	return false
end

function glOMP.View:create(name, defaults)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		defaults = name
		name = UUID()
	end

	if _g_views[name] then
		error ("Existing view found (Perhaps you want 'get_or_create'?): " .. name)
		return false
	end

	local new_view = self:extend({
				name = name,
				sub_children = {},
				children = {},
				event_pump = glOMP.EventPump.load(name)
			})

	_g_views[name] = new_view

	_g_table_utils.set_defaults(new_view, defaults)

	return new_view
end

function glOMP.View.clone(name)
	
end

function glOMP.View:extend(mixin)
	return _g_table_utils.extend(self, mixin)
end