local button = definition.workon("simple_gui_button")

button.defaults.x = 0
button.defaults.y = 0
button.defaults.width   = 100
button.defaults.height  = 100
button.defaults.text    = "Button"
button.defaults.label   = description.workon("gui_button_label")
button.defaults.normal_color        = 0xffffff
button.defaults.mouse_over_color    = 0xffffff
button.defaults.pressed_color       = 0xffffff
button.defaults.disabled_color      = 0xffffff
button.defaults.current_color       = button.defaults.normal_color



button.default_events:on("draw", function (data, caller, context)
                props = called:all()
                if props.current_color then
                    glomp.graphics.push_matrix()
                    glomp.graphics.translate(props.x, props.y)
                    props.current_color.events:trigger("draw")
                    glomp.graphics.pop_matrix()
                end
            end)
