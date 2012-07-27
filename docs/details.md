Elements:
	
	Have counterparts in render thread (and physics thread eventually)
	Have very narrow and concise functionality
	Most basic are represented as userdata
	Compositions are Lua tables 
		Refer to other elements as handles
		I.E. a sprite might have a transform handle, a texture handle and a mesh handle
	Are interfaced with through actions:
		LoadImage(file, properties)
		Move(newX, newY)
		Rotate(angle)
	Actions return the object, for chaining:
		Load().Move().Rotate()
	Actions are reversible under the hood, sent via notifications

Events/Notifications:

	Agents notify the main thread of any changes
	Main thread notifies others of it's changes IF subscribed (flag on an object)


Main thread loop:
	
	openFrameworks driven through lua proxy

	update:
		process notifications,
		update any update-able objects
	render:
		loop through scene graphs
	events:
		send notifications
