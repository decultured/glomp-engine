local tile_map = definition.workon("simple_gui_tile_map", "simple_gui_sprite_sheet")

tile_map.defaults.tiles_wide = 100
tile_map.defaults.tiles_high = 100
tile_map.defaults.total_tiles = 100000

tile_map.defaults.tiles = {}

function draw_tiles(data, context)
    
end

tile_map.events:on("apply", function (data, context)
    context.events:off("draw")
    context.events:on("draw", draw_tiles)
end)

tile_map.default_events:on({"tiles_wide", "tiles_high"}, function (data, context)
    make_tiles()
end)

tile_map.methods.make_tiles = function (self)
    local props = self:all()

    self:set("total_tiles", props.tiles_wide * props.tiles_high)

    if #(props.tiles) < props.total_tiles then
        local start = 1
        if #(props.tiles) then
            start = #(props.tiles)
        end

        for i = start, props.total_tiles do
            props.tiles[i] = 0
        end
    end
end