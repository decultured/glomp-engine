function printobj(obj)
	print ("\nObject:")
	for key, val in pairs(obj) do
		print(key, val)
	end

	if (obj.__index) then
		print ("\n__Index:")	
		for key, val in pairs(obj.__index) do
			print(key, val)
		end
	end
end