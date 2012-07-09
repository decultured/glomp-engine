function glomp_printobj(obj)
	print ("\nObject:")
	for key, val in ipairs(obj) do
		print(key, val)
	end

	if (obj.__index) then
		print ("\n__Index:")	
		for key, val in ipairs(obj.__index) do
			print(key, val)
		end
	end
end

-- This runs a script within a specified environment
-- this prevents it from polluting the global namespace
function run(scriptfile)
    local env = setmetatable({}, {__index=_G})
    assert(pcall(setfenv(assert(loadfile(scriptfile)), env)))
    setmetatable(env, nil)
    return env
end