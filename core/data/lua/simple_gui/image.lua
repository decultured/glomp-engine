local image = definition.workon("simple_gui_image", "simple_gui_element")
local set_color_hex = glomp.graphics.set_color_hex

image.defaults.x = 0
image.defaults.y = 0
image.defaults.image = nil
image.defaults.color = 0xffffff

image.default_events:on("draw", function (data, context)
                props = context:all()
                set_color_hex(props.color)
                if props.image then
                    props.image:draw(props.x, props.y)
                end
            end)
