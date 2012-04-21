/*
 * 	main.cpp
 *
 * 	glomp engine starts here!
 *
 */

#define GLOMP_PLATFORM_OSX

#include <GL/glfw.h>
#include <gl.h>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <iostream>
#include <fstream>

#include "app/Window.h"
#include "app/StageMachine.h"

#include "app/appBinding.h"
#include "common/TimerBinding.h"
#include "input/InputBinding.h"
#include "audio/AudioBinding.h"
#include "audio/SoundBinding.h"

#include "graphics/ImageBinding.h"


bool force_quit = false;

void lua_command_line(lua_State *L) {
	std::string buffer;
	int error;

	while (std::getline(std::cin, buffer)) {
		error = luaL_loadbuffer(L, buffer.c_str(), buffer.length(), "line") || lua_pcall(L,0,0,0);

		if (error) {
			std::cerr << "\n\033[1;31m" << lua_tostring(L, -1) << "\033[0m\n";
			lua_pop(L, 1);
		}

		if (force_quit) break;
	}
	glfwTerminate();
	return;
}

static int quit(lua_State *L) {
	force_quit = true;
	return 0;
}

bool file_exists(const char *filename) {
	std::ifstream file(filename);
	return file;
}

int main(int argc, char *argv[]) {

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	glomp::app::luaopen_window(L);
	glomp::util::luaopen_timer(L);
	glomp::input::luaopen_input(L);
	glomp::audio::luaopen_audio(L);
	glomp::audio::luaopen_sound(L);
	glomp::graphics::luaopen_image(L);

	lua_pushcfunction(L, quit);
	lua_setglobal(L, "quit");

	if (argc > 1) {
		if (luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
			std::cerr << "cannot run config. file:" << lua_tostring(L, -1) << "\nNum arguments: " << argc << "\n";
	} else if (file_exists("main.lua")) {
		if (luaL_loadfile(L, "main.lua") || lua_pcall(L, 0, 0, 0)) {


		}
	} else {
		std::cout << "No lua file found, running interactive command line tester.\nEnter \"quit()\" to quit.\n\n";
		lua_command_line(L);
	}

	lua_close(L);


	// Exit program
	return 0;
}
