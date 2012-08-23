load_module("lib/lunatest")

local testbed = {1,2,3,4,5,6,7,8,9,10}

local test_model = description.workon(testbed)
local table_utils = table_utils or {}

local model_tests = {}

function model_tests:test_model_set_get()
	test_model:set("this", "Is")
	assert_equal(test_model:get("this"), "Is")
end

function model_tests:test_map()
	local map = table_utils.map(testbed, function (val)
		return val + 10
	end)
	assert_equal(json.encode(map), "[11,12,13,14,15,16,17,18,19,20]")
end

function model_tests:test_reduce()
	local reduce = table_utils.reduce(testbed, function(val, key, memo) 
		return val + memo
	end, 0)
	assert_equal(reduce, 55)
end

function model_tests:test_find()
	local find = table_utils.find(testbed, function(val)
		return val == 7
	end)
	assert_equal(find, 7)
end

function model_tests:test_filter()
	local filter = table_utils.filter(testbed, function (val)
		return val > 5
	end)
	assert_equal(json.encode(filter), "[6,7,8,9,10]")
end

function model_tests:test_max()
	local max = table_utils.max(testbed)
	assert_equal(max, 10)
end

lunatest.run_embeded(model_tests, "Model Tests", false)