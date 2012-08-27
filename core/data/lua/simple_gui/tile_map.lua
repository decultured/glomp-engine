local tile_map = definition.workon("simple_gui_tile_map", "simple_gui_sprite_sheet")

tile_map.defaults.tile_width = 30
tile_map.defaults.tile_height = 30
tile_map.defaults.tiles_wide = 70
tile_map.defaults.tiles_high = 50
tile_map.defaults.total_tiles = 100000

tile_map.defaults.tiles = {}

function draw_tiles(data, context)
    local props = context:all()

    local image = props.image
    local draw = props.image.draw_subsection
    local x = 0
    local y = 0
    local cols = 0
    local frames = props.frames.list
    local image_width = props.image_width
    local image_height = props.image_height
    local tile_width = props.tile_width
    local tile_height = props.tile_height
    local source_width = image_width / props.frames_wide
    local source_height = image_height / props.frames_high

    local frame
    for i = 1, #(props.tiles) do

        if not props.tiles[i] then
            return
        end
        
        frame = frames[props.tiles[i]].fields
        
        draw(image, x, y, tile_width, tile_height, 
            frame.source_x, frame.source_y, source_width, source_height)
        x = x + tile_width
        cols = cols + 1
        if cols >= props.tiles_wide then
            cols = 0
            x = 0
            y = y + tile_height
        end
    end
end

tile_map.events:on("apply", function (data, context)
    context.events:off("draw")
    context.events:on("draw", draw_tiles)
    context:make_tiles()
    context:make_random()
end)

tile_map.default_events:on({"tiles_wide", "tiles_high"}, function (data, context)
    context:build_frames()
    context:make_tiles()
    context:make_random()
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

tile_map.methods.make_random = function (self)
    local props = self:all()

    local frames = #(props.frames.list)

    for i = 1, #(props.tiles) do
        props.tiles[i] = 1
    end
end