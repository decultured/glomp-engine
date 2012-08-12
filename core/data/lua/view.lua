glOMP = glOMP or {}
local _g_table_utils = glOMP.table_utils
local _g_graphics = glOMP.graphics

local _view_meta = {}

function _view_meta:render( )
	if not self._description:get("enabled") then
		return
	end

	self:push()

	_g_table_utils.call_each(self._sub_children, "render")

	if self._description:get("visible") then
		self:draw()
	end

	_g_table_utils.call_each(self._children, "render")

	self:pop()	
end

function _view_meta:add_child(view)
	table.insert(self._children, view)
end

function _view_meta:add_sub_child(view)
	table.insert(self._sub_children, view)
end

function _view_meta:remove_child(view)
	_g_table_utils.remove_one(self._children, view)
end

function _view_meta:remove_sub_child(view)
	_g_table_utils.remove_one(self._sub_children, view)
end

function _view_meta:push()
	_g_graphics.push_matrix()

	local attr = self._description:all()

	_g_graphics.translate(attr.x, attr.y)
	_g_graphics.rotate(attr.rotation)
	_g_graphics.translate(attr.scale_x, attr.scale_y)
end

function _view_meta:pop()
	_g_graphics.pop_matrix()
end

function _view_meta:initialize()

end

function _view_meta:draw()
	glOMP.graphics.set_color(hex_to_rgb("#ede9d6"))
	glOMP.graphics.draw_fills(true)
	glOMP.graphics.enable_smoothing()
	glOMP.graphics.rectangle(10, 10, 500, 200)
	glOMP.graphics.draw_fills(false)
	glOMP.graphics.set_circle_resolution(100)
	glOMP.graphics.set_line_width(3)
	glOMP.graphics.set_color(hex_to_rgb("#5a6e75"))
	glOMP.graphics.rectangle(10, 10, 500, 200)
end

_view_meta.__index = _view_meta

glOMP.View = glOMP.View or {}

glOMP.store = glOMP.store or {}
glOMP.store.views = glOMP.store.views or {}
local _g_views = glOMP.store.views

function glOMP.View:load(name, description)
	if not name then
		name = UUID()
	elseif type(name) == "table" then
		initial = name
		name = UUID()
	end

	if _g_views[name] then
		print ("Existing View Found: " .. name)
		return _g_views[name]
	end

	description = description or glOMP.Description:load()

	description:set_defaults({
			x = 0,
			y = 0,
			rotation = 0,
			scale_x = 0,
			scale_y = 0,
			enabled = true,
			visible = true
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

	_g_views[name] = new_view
	
	return new_view
end

function glOMP.View:extend(mixin)
	return _g_table_utils.extend(self, mixin)
end