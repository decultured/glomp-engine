dofile("lua/input_defines.lua")
dofile("lua/game_config.lua")
dofile("lua/util.lua")
dofile("lua/game_object.lua")
dofile("lua/game_loop.lua")
dofile("lua/world.lua")
dofile("lua/projectiles.lua")
dofile("lua/planet.lua")
dofile("lua/player.lua")
dofile("lua/background_obj.lua")
dofile("lua/menu.lua")
dofile("lua/enemies.lua")


game_window:set_clear_color(0.0, 0.0, 0.0)
bind_actions(game_bindings)

meteor = background_object:new({name = "meteor", x = 45, y = 800})
meteor2 = background_object:new({name = "meteor2", x = 140, y = 900})

wave = 2
local foe_count = 0

foes = {}

function create_foes(num_foes)
	local last = 1
	for k, v in ipairs(death_balls) do
		last = k
	end

	for i=last,last + num_foes do
		foes[i] = enemy_obj:new({
			name = "saucer",
			y = 2000,
			x = math.random(0, 360),
		},{
			hover_dist = math.random(250, 600) + planet.radius,
			speed = math.random(10, 50),
		})
	end
end

stars = {}
local num_stars = 500
for i=1,num_stars do
	local star = star_object:new({
		name = "star",
		y = math.random(0, 1000) + planet.radius,
		x = math.random() * 360.0,
		tx = math.random(0, 4) * 0.25,
		ty = math.random(0, 4) * 0.25,
		a = math.random() * 0.5 + 0.2
	},
	{
		rotation_speed = math.random(0, 16) - 8
	})
	stars[i] = star
end

for i=1,num_stars do
	local star = star_object:new({
		name = "star",
		y = math.random(0, 1000) + planet.radius,
		x = math.random() * 360.0,
		tx = math.random(0, 4) * 0.25,
		ty = math.random(0, 4) * 0.25,
		width = 4,
		height = 4
	},
	{
		rotation_speed = math.random(0, 16) - 8
	})
	stars[i + 1000] = star
end

elapsed_frame_time = 0
frames = 0

function main_loop(seconds)
	world.start_frame(seconds)
			
	
		for k, v in ipairs(stars) do
			v:update(seconds)
		end
		foe_count = 0
		for k, v in next, foes do
			v:update(seconds)
			foe_count = foe_count + 1
		end
		if (foe_count < 1) then 
			wave = wave + 1
			sounds.nextwav:play()
			create_foes(wave)
		end


		planet.update(seconds)

		for k, v in next, bullets do
			if v.dead then
				bullets[k] = nil
			end
			v:update(seconds)
			r, d = v.sprite:position()
			
			for k2, v2 in next, foes do
				if v2:collides_with(r, d, 50) then
					v2.life = v2.life - v.power
					if v2.life < 0 then
						sounds.explode:play()
						foes[k2] = nil
					else
						sounds.hit:play()
					end
					bullets[k] = nil
				end
			end
		end
		for k, v in next, death_balls do
			if v.dead then
				death_balls[k] = nil
			end
			v:update(seconds)
			r, d = v.sprite:position()
			
			if player:collides_with(r, d, 50) then
				player.life = player.life - v.power
				if player.life < 0 then
					sounds.explode:play()
					state = "dead"
--					Game Over!
				else
					sounds.hit:play()
				end
				death_balls[k] = nil
			end
		end

		player.update(seconds)
		meteor:update(seconds)
		meteor2:update(seconds)

	world.end_frame(seconds)
end

menu = menu_object:new({}, {});
died_screen = game_over_object:new({}, {});

game_input:on("menu_done", function () 
	if state == "menu" then
		player.life = game_options.player_life
		foes = {}
		bullets = {}
		death_balls = {}
		player.obj:position(45, planet.radius)
		create_foes(2)
		state = "game"
	elseif state == "dead" then
		state = "menu"
	end
end)

game_loop(function (seconds) 
	if state == "menu" then
		menu:update(seconds)
	elseif state == "dead" then
		died_screen:update(seconds)
	else
		main_loop(seconds)
	end
end)
