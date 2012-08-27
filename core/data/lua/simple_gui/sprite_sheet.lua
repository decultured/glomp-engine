local sprite_sheet = definition.workon("simple_gui_sprite_sheet", "simple_gui_partial_image")

local sprite_sheet_frame = definition.workon("simple_gui_sprite_sheet_frame", "simple_gui_partial_image")

sprite_sheet_frame.defaults.index   = 1
sprite_sheet_frame.source_x         = 0
sprite_sheet_frame.source_y         = 0
sprite_sheet_frame.source_width     = 0
sprite_sheet_frame.source_height    = 0

sprite_sheet.defaults.image         = nil
sprite_sheet.defaults.color         = 0xffffff
sprite_sheet.defaults.source_x      = 0
sprite_sheet.defaults.source_y      = 0
sprite_sheet.defaults.source_width  = 100
sprite_sheet.defaults.source_height = 100
sprite_sheet.defaults.image_width   = 100
sprite_sheet.defaults.image_height  = 100

sprite_sheet.defaults.current_frame = 1

sprite_sheet.defaults.self_build    = true
sprite_sheet.defaults.frames_wide   = 1
sprite_sheet.defaults.frames_high   = 1

sprite_sheet.defaults.total_frames  = 1
sprite_sheet.defaults.frames        = nil

sprite_sheet.default_events:on({"image_width", "image_height", "frames_wide", "frames_high"}, function (data, context)
    if context:get("self_build") then
        context:build_frames()
    end
end)

sprite_sheet.default_events:on("current_frame", function (data, context)
        local props = context:all()
        local frames = props.frames
        local new_props = {}

        if frames:len() ~= props.total_frames then
            if props.self_build then
                context:build_frames()
            end
        end

        if not frames:len() or props.current_frame > frames:len() or props.current_frame < 1 then
            warning("Invalid sprite frame selected for: "..context.name.." : "..props.current_frame)
            context:set("current_frame", 1)
            return
        end

        local frame_props = frames:get(props.current_frame):all()

        new_props.source_x      = frame_props.source_x
        new_props.source_y      = frame_props.source_y
        new_props.source_width  = frame_props.source_width
        new_props.source_height = frame_props.source_height

        context:set(new_props)
    end)

sprite_sheet.events:on("apply", function (data, context)
        if context:get("frames") then
            return
        end
        local frames = collection.workon(context.name.."_frames", "simple_gui_sprite_sheet_frame")
        context:set("frames", frames)
    end)

sprite_sheet.methods.build_frames = function (self)
    local props = self:all()

    if props.frames_wide < 1 or props.frames_high < 1 then
        warning("Invalid number of frames")
        return
    end

    if not props.image then
        warning("Needs an image")
        return
    end

    local total_frames = props.frames_wide * props.frames_high

    if props.frames:len() > total_frames then
        -- TODO: remove excess frames?
    elseif props.frames:len() < total_frames then
        local difference = total_frames - props.frames:len()
        local current = props.frames:len() or 0
        for i = 1, difference do
            current = current + 1
            props.frames:add(description.workon(self.name.."_frame_"..current, "simple_gui_sprite_sheet_frame"))
        end
    end

    self:set({
            image_width = props.image:get_width(),
            image_height = props.image:get_height(),
            total_frames = props.frames_wide * props.frames_high
        })

    local source_width = props.image_width / props.frames_wide
    local source_height = props.image_height / props.frames_high

    local frame
    local frame_num = 1
    for y = 1, props.frames_high do
        for x = 1, props.frames_wide do
            frame = props.frames:get(frame_num)
            if frame then
                frame_num = frame_num + 1

                frame:set({
                        source_x = (x - 1) * source_width,
                        source_y = (y - 1) * source_height,
                        source_width = source_width,
                        source_height = source_height,
                    })
            else
                print (frame_num, props.frames_high, props.frames_wide, props.frames:len())
            end
        end
    end
end

-- TODO : setup tick thing here
local function cycler()
    local frame = sprite_test:get("current_frame") + 1
    if frame > sprite_test:get("frames_wide") * sprite_test:get("frames_high") then
        frame = 1
    end
    sprite_test:set("current_frame", frame)
end
