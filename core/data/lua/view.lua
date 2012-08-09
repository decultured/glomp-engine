local _view_proto = {}

function _view_proto:render( )
	
end

function _view_proto:add_right_child(view)
	
end

function _view_proto:add_left_child(view)
	
end

function _view_proto:remove_right_child(view)

end

function _view_proto:remove_left_child(view)

end

_view_proto.__index = _view_proto

View = {}

function View.new(options)
	local new_view = {
			_left_children = {},
			_right_children = {},
		}
end

