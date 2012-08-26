local image = definition.workon("simple_gui_image", "simple_gui_element")

image.defaults.x = 0
image.defaults.y = 0
image.defaults.width = 100
image.defaults.height = 100
image.defaults.image = nil
image.defaults.color = 0xffffff

image.default_events:on("image", function (data, context)
    if not data then
        return
    end

    context:set({
        width = data:get_width(),
        height = data:get_height()
    })

end)

image.default_events:on("draw", function (data, context)
                props = context:all()
                if props.image then
                    props.image:draw()
                end
            end)
