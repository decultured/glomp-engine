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