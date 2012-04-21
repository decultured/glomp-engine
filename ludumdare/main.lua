require "game_loop"

times = timer.new()
times:start()

frames = game_loop()

times:stop()

local elapsed = times:elapsed()
local fps = frames / elapsed
print("Ran in", elapsed, "seconds\nOr", fps, "fps")
