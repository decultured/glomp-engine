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

#include <iostream>
#include "app/StageMachine.h"

glomp::app::Window app;

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

int glfw_test() {
	// Initialize GLFW
	if( !glfwInit() )
	{
		return -1;
	}
	// Open an OpenGL window
	if( !glfwOpenWindow( 800,600, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return -1;
	}

	glClearColor(1.0, 0.0, 0.0, 1.0);

	glomp::StageMachine stage_machine;

	stage_machine.run();

	glfwTerminate();

	return 0;
}

static int run(lua_State *L) {
//	glfw_test();
	glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();

	return 0;
}

static int init(lua_State *L) {
	int width = lua_tonumber(L, 1);
	int height = lua_tonumber(L, 2);
	app.init(width, height, 8, false);
	return 0;
}

static int shutdown(lua_State *L) {
	app.shutdown();

	return 0;
}

static int quit(lua_State *L) {
	force_quit = true;
	return 0;
}

static int backgroundColor(lua_State *L) {
	float r = luaL_checknumber(L, 1);
	float g = luaL_checknumber(L, 2);
	float b = luaL_checknumber(L, 3);

	glClearColor(r, g, b, 1.0);
	return 0;
}

int main(int argc, char *argv[]) {

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, run);
	lua_setglobal(L, "update");
	lua_pushcfunction(L, init);
	lua_setglobal(L, "init");
	lua_pushcfunction(L, shutdown);
	lua_setglobal(L, "shutdown");
	lua_pushcfunction(L, quit);
	lua_setglobal(L, "quit");
	lua_pushcfunction(L, backgroundColor);
	lua_setglobal(L, "background_color");

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
