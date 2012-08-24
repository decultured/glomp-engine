local image = definition.workon("simple_gui_image")

image.defaults.x = 0
image.defaults.y = 0
image.defaults.image = nil
image.default_events:on("draw", function (data, caller, called)
                props = called:all()
                if props.image then
                    props.image:draw(props.x, props.y)
                end
            end)
