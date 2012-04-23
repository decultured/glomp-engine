state = "menu"

performance_timer = timer.new()

game_frame_time = 0
game_time = 0
game_timer = timer.new()
game_input = input.new()
game_audio = audio.new()

sounds = {}
sounds.bew = sound.new()
sounds.bew:load_wav("sounds/bew.wav")
sounds.explode = sound.new()
sounds.explode:load_wav("sounds/explode.wav")
sounds.motor = sound.new()
sounds.motor:load_wav("sounds/motor.wav")
sounds.hit = sound.new()
sounds.hit:load_wav("sounds/hit.wav")
sounds.nextwav = sound.new()
sounds.nextwav:load_wav("sounds/next.wav")


game_options = {
	screen_width = 1024,
	screen_height = 576,
	
	draw_width = 1024,
	screen_height = 576,
	
	gravity = 900,
	
	world_x = 1024 * 0.4,
	world_y = -200,
	world_v_offset = 768 * 0.15,

	world_scale = 0.7,
	
	player_speed = 100,
	player_life = 50
}

game_bindings = {
	{"quit", "key_down", keyboard.ESC},

	{"fire", "key_is_down", keyboard.Z},
	{"fire", "key_is_down", keyboard.SPACE},

	{"jump", "key_down", keyboard.UP},
	{"jump", "key_down", keyboard.A},

	{"right", "key_is_down", keyboard.RIGHT},
	{"right", "key_is_down", keyboard.D},

	{"left", "key_is_down", keyboard.LEFT},
	{"left", "key_is_down", keyboard.A},

	{"right_stop", "key_up", keyboard.RIGHT},
	{"right_stop", "key_up", keyboard.D},

	{"left_stop", "key_up", keyboard.LEFT},
	{"left_stop", "key_up", keyboard.A},

	{"menu_done", "key_down", keyboard.ENTER},
}

game_window = window.new()
game_window:init(game_options.screen_width, 
				game_options.screen_height,
				true)

player_bullet_image = image.new()
player_bullet_image:load("images/bullet.tga")
bullet_image = image.new()
bullet_image:load("images/bullet.tga")
player_image = image.new()
player_image:load("images/player.tga")
planet_tex = image.new()
planet_tex:load("images/world.tga")
menu_image = image.new()
menu_image:load("images/menu.tga")
saucer_image = image.new()
saucer_image:load("images/saucer.tga")
meteor_image = image.new()
meteor_image:load("images/meteors.tga")
stars_image = image.new()
stars_image:load("images/stars.tga")

