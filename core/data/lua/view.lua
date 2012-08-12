glOMP = glOMP or {}
local _g_table_utils = glOMP.table_utils
local _g_graphics = glOMP.graphics

local _view_meta = {}

function _view_meta:render( )
	self:push()

	_g_table_utils.call_each(_sub_children, "render")

	self:draw()

	_g_table_utils.call_each(_children, "render")

	self:pop()	
end

function _view_meta:add_child(view)
	table.insert(self._children, view)
end

function _view_meta:add_sub_child(view)
	table.insert(self._children, view)
end

function _view_meta:remove_child(view)
	_g_table_utils.remove_one(self._children, view)
end

function _view_meta:remove_sub_child(view)
	_g_table_utils.remove_one(self._sub_children, view)
end

function _view_meta:push()
	local attr = self._description:all()
	_g_graphics.translate(attr.x, attr.y)
	_g_graphics.rotate(attr.rotation)
	_g_graphics.translate(attr.scale_x, attr.scale_y)
	_g_graphics.push_matrix()
end

function _view_meta:pop()
	_g_graphics.pop_matrix()
end

function _view_meta:draw()

end

_view_meta.__index = _view_meta

glOMP.View = glOMP.View or {}

function glOMP.View:load(name, description)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		initial = name
		name = UUID()
	end

	description = description or glOMP.Description:load()

	description:set_defaults({
			x = 0,
			y = 0,
			rotation = 0,
			scale_x = 0,
			scale_y = 0
		})

	print("New view: "..name)
	local new_view = _g_table_utils.extend(self, {
				_name = name,
				_sub_children = {},
				_children = {},
				_description = description,
				_event_pump = glOMP.EventPump.load(name)
			})

	setmetatable(new_view, _view_meta)
	if initial then
		new_view:set_many(initial, {silent = true})
	end
	return new_view
end

function glOMP.View:extend(mixin)
	return _g_table_utils.extend(self, mixin)
end