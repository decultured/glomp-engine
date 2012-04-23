function fire(self)
	self.fire_elapsed = game_frame_time + self.fire_elapsed
	if self.fire_elapsed < self.fire_rate then
		return
	else
		self.fire_elapsed = 0
		self.fire_rate = (math.random() * (self.fire_rate_max - self.fire_rate_min)) + self.fire_rate_min
	end

	local x_pos, y_pos = self.sprite:position()

	local death_ball = death_ball_obj:new({
		x = x_pos,
		y = y_pos
	},{
			
	})
	
	local last = 0
	for k, v in ipairs(death_balls) do
		if not v then
			death_balls[k] = death_ball
			last = -1
			break
		end
		last = k
	end
	if last > -1 then
		death_balls[last +1] = death_ball
	end
end

enemy_obj = game_object:new({
	texture_id = saucer_image:get_id(),
	tx = 0.0,
	ty = 0.75,
	tw = 0.50,
	th = 0.25,
	width = 128,
	height = 64
}, 
{
	hover_dist = 250 + planet.radius,
	speed = 50,	
	d_accel = 100,
	d_speed = -50,
	tolerance = 30,
	life = 200,
	damper = 2,
	fire_rate_min = 1,
	fire_rate_max = 5,
	last_fired = -1000,
	fire_rate = -1000,
	fire_elapsed = 0,
	fire = fire
})

enemy_obj:on_update(function (self, seconds)
	local r, d = self.sprite:translate(seconds * self.speed, 0.0)

	if self.fire_rate < 0 then
		self.fire_rate = (math.random() * (self.fire_rate_max - self.fire_rate_min)) + self.fire_rate_min
	end
	self:fire()


	if d > self.hover_dist + self.tolerance then
		self.d_speed = self.d_speed - (self.d_accel * seconds) 
		d = d + (self.d_speed * seconds)
		self.sprite:position(r, d)
	elseif d > self.hover_dist then
		self.d_speed = (self.d_speed - (self.d_accel * seconds)) * (1 - (seconds * self.damper))
		d = d + (self.d_speed * seconds)
		self.sprite:position(r, d)
	elseif d < self.hover_dist then
		self.d_speed = (self.d_speed + (self.d_accel * 10 * seconds)) * (1 - (seconds * self.damper))
		d = d + (self.d_speed * seconds)
		self.sprite:position(r, d)
	end
end)

function enemy_obj:collides_with(two_rad, two_d, two_size)
	local two_width = two_size * 0.5
	local two_height = two_size * 0.5
	local one_rad, one_d = self.sprite:position()
	local one_width, one_height = self.sprite:size()
	one_width = one_width * 0.5
	one_height = one_height * 0.5


	local coll = false

	if two_d - two_height > one_d + one_height or two_d + two_height < one_d - one_height then
		return false
	end

	-- testee angle - testee angular width
	local one_l = (one_rad - 2)
	-- testee angle - testee angular width
	local one_r = (one_rad + 2)
	-- testing.getRotation() + testingAngle
	local two_l = (two_rad - 1)
	-- testing.getRotation() - testingAngle
	local two_r = (two_rad + 1)
	

	if one_l < two_l and one_l > two_r then
		coll = true
	elseif one_r > two_r and one_r < two_l then
		coll = true

	elseif one_l < two_r and one_r > two_l then
		coll = true
	elseif one_l > two_r and one_r < two_l then
		coll = true
	end


	return coll
end

