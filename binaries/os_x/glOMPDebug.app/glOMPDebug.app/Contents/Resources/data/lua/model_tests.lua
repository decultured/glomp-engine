local testbed = {1,2,3,4,5,6,7,8,9,0}



glomp = glomp or {}

local test_model = _.extend(glomp.Model, { })

test_model:set("this", "Is")

print(test_model:get("this"))

local reduce = _.reduce(testbed, function(val, key, memo) 
	return val + memo
end, 0)

print (reduce)

local find = _.find(testbed, function(val)
	return val == 7
end)

print (find)

local filter = _.filter(testbed, function (val)
	return val > 5
end)

print (filter)

