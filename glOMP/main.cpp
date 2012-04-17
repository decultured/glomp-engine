/*
 * 	main.cpp
 *
 * 	glomp engine starts here!
 *
 */


#include <GL/glfw.h>
#include <opengl.h>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "app/Window.h"
#include "app/appBinding.h"

#include <iostream>
#include "app/StageMachine.h"

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

int main(int argc, char *argv[]) {

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	glomp::app::luaopen_window(L);

	lua_pushcfunction(L, quit);
	lua_setglobal(L, "quit");

	if (argc > 1) {
		if (luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
			std::cerr << "cannot run config. file:" << lua_tostring(L, -1) << "\nNum arguments: " << argc << "\n";
	} else {
		lua_command_line(L);
	}

	lua_close(L);

	// Exit program
	return 0;
}
