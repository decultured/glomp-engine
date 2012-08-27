local root_window  = description.workon("root_window", "simple_gui_root")

local startup_scene  = description.workon("startup_scene", "simple_gui_root")
local game_scene = description.workon("game_scene", "simple_gui_root")

local game_state = description.workon("game_state")
local performance = description.workon("debug_performance_display", "simple_gui_label")

game_state.events:on("scene", function (data, context)
    local props = context:all()

    context:get("game_scene"):set("visible", false)
    context:get("startup_scene"):set("visible", false)

    print(props.scene.name)
    
    show_scene()
end)

function show_scene()
    game_state:get("scene"):set("visible", true)
end

game_state:set({
        startup_scene = startup_scene,
        game_scene = game_scene,

        scene = startup_scene
    })

root_window:add_children(startup_scene, game_scene, performance)