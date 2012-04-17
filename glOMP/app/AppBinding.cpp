/*
 * AppBinding.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: jgraves
 */

#include "AppBinding.h"
extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include <iostream>
#include <GL/glfw.h>
#include <opengl.h>

namespace glomp {
namespace app {

#define glomp_checkwindow(L, N) *(Window **)luaL_checkudata(L, N, "glomp.window")

static int glomp_window_new(lua_State *L) {
	Window **new_win = (Window **)lua_newuserdata(L, sizeof(Window *));
	luaL_getmetatable(L, "glomp.window");
	lua_setmetatable(L, -2);

	*new_win = new Window();

	return 1;
}

static int glomp_window_init(lua_State *L)
{
	Window *win = glomp_checkwindow(L, 1);

	int width = luaL_checknumber(L, 2);
	int height = luaL_checknumber(L, 3);

	win->init(width, height, 8, false);

	return 0;
}

static int glomp_window_resize(lua_State *L)
{
	Window *win = glomp_checkwindow(L, 1);

	int width = luaL_checknumber(L, 2);
	int height = luaL_checknumber(L, 3);

	win->resize(width, height, false);
	return 0;
}

static int glomp_window_clear(lua_State *L)
{
	Window *win = glomp_checkwindow(L, 1);

	win->clear();
	return 0;
}

static int glomp_window_clearcolor(lua_State *L) {
	Window *win = glomp_checkwindow(L, 1);
	float r = luaL_checknumber(L, 2);
	float g = luaL_checknumber(L, 3);
	float b = luaL_checknumber(L, 4);

	win->set_clear_color(r, g, b);

	return 0;
}

static int glomp_window_shutdown(lua_State *L)
{
	Window *win = glomp_checkwindow(L, 1);
	win->shutdown();
	return 0;
}

static int glomp_window_gc(lua_State *L) {
	Window *win = glomp_checkwindow(L, 1);
	delete win;
	return 0;
}

static const struct luaL_Reg glomp_window_main [] = {
		{"new", glomp_window_new},
		{NULL, NULL}
};

static const struct luaL_Reg glomp_window_funcs [] = {
	{"init", glomp_window_init},
	{"resize", glomp_window_resize},
	{"clear", glomp_window_clear},
	{"set_clear_color", glomp_window_clearcolor},
	{"shutdown", glomp_window_shutdown},
	{"__gc", glomp_window_gc},
	{NULL, NULL}
};

int luaopen_window (lua_State *L) {
	luaL_newmetatable(L, "glomp.window");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_window_funcs, 0);

	luaL_newlib(L, glomp_window_main);
	lua_setglobal(L, "window");
	return 1;
}

} /* namespace app */
} /* namespace glomp */
