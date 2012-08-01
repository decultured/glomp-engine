require("lunatest")

glomp = glomp or {}

local test_model = _.extend(glomp.Model, { })
local testbed = {1,2,3,4,5,6,7,8,9,10}

function test_model_set_get()
	test_model:set("this", "Is")
	assert_equal(test_model:get("this"), "Is")
end

function test_map()
	local map = _.map(testbed, function (val)
		return val + 10
	end)
	assert_equal(json.encode(map), "[11,12,13,14,15,16,17,18,19,20]")
end

function test_reduce()
	local reduce = _.reduce(testbed, function(val, key, memo) 
		return val + memo
	end, 0)
	assert_equal(reduce, 55)
end

function test_find()
	local find = _.find(testbed, function(val)
		return val == 7
	end)
	assert_equal(find, 7)
end

function test_filter()
	local filter = _.filter(testbed, function (val)
		return val > 5
	end)
	assert_equal(json.encode(filter), "[6,7,8,9,10]")
end

function test_max()
	local max = _.max(testbed)
	assert_equal(max, 10)
end

lunatest.run()