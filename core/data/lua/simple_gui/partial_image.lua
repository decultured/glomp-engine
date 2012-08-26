local partial_image = definition.workon("simple_gui_partial_image", "simple_gui_element")

partial_image.defaults.image = nil
partial_image.defaults.color = 0xffffff
partial_image.defaults.source_x = 0
partial_image.defaults.source_y = 0
partial_image.defaults.source_width = 100
partial_image.defaults.source_height = 100

partial_image.default_events:on("image", function (data, context)
    if not data then
        return
    end

    context:set({
        image_width = data:get_width(),
        image_height = data:get_height()
    })
end)

partial_image.default_events:on("draw", function (data, context)
        props = context:all()
        if props.image then
            props.image:draw_subsection(0, 0, props.width, props.height, 
                                        props.source_x, props.source_y,
                                        props.source_width, props.source_height)
        end
    end)
