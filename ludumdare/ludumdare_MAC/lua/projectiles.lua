bullets = {}

bullet_obj = game_object:new({
	texture_id = bullet_image:get_id(),
	tx = 0.0,
	ty = 0.5,
	tw = 0.5,
	th = 0.5,
	width = 32,
	height = 32
}, 
{
	power = 100,
	lifespan = 2,
	elapsed = 0,
	dead = false,
	speed = 50,
	velocity_d = 900, 
	velocity_r = 0
})

bullet_obj:on_update(function (self, seconds)
	local spr = self.sprite
	self.elapsed = self.elapsed + seconds
	if self.elapsed > self.lifespan then
		self.dead = true
	end
	
--	spr:translate(seconds * self.speed, 0.0)
	
--	self.velocity_d = self.velocity_d - (seconds * game_options.gravity)
	r, d = spr:translate(0, self.velocity_d * seconds)

	if d < planet.radius and self.velocity_d < 0 then
		self.velocity_d = - self.velocity_d * 0.5
		spr:position(r, planet.radius)
	end
	
	spr:rotate(360*seconds)

end)


death_balls = {}

death_ball_image = image.new()
death_ball_image:load("death_ball.tga")

death_ball_obj = game_object:new({
	texture_id = bullet_image:get_id(),
	tx = 0.5,
	ty = 0.5,
	tw = 0.5,
	th = 0.5,
	width = 32,
	height = 32
}, 
{
	power = 10,
	lifespan = 2,
	elapsed = 0,
	dead = false,
	speed = 10,
	velocity_d = -50, 
	velocity_r = 0
})

death_ball_obj:on_update(function (self, seconds)
	local spr = self.sprite
	self.elapsed = self.elapsed + seconds
	if self.elapsed > self.lifespan then
		self.dead = true
	end
	
	spr:translate(seconds * self.speed, 0.0)
	
	self.velocity_d = self.velocity_d - (seconds * game_options.gravity)
	r, d = spr:translate(0, self.velocity_d * seconds)

	if d < planet.radius and self.velocity_d < 0 then
		self.velocity_d = - self.velocity_d * 0.5
		spr:position(r, planet.radius)
	end
	
	spr:rotate(360*seconds)

end)
