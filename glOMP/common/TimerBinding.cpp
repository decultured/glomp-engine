/*
 * TimerBinding.cpp
 *
 *  Created on: Apr 17, 2012
 *      Author: jgraves
 */

#include "TimerBinding.h"

namespace glomp {
namespace util {

#define glomp_checktimer(L, N) *(Timer **)luaL_checkudata(L, N, "glomp.timer")

int glomp_timer_new(lua_State *L) {
	Timer **new_timer = (Timer **)lua_newuserdata(L, sizeof(Timer *));
	luaL_getmetatable(L, "glomp.timer");
	lua_setmetatable(L, -2);

	*new_timer = new Timer();

	return 1;
}

int glomp_timer_gc(lua_State *L) {
	Timer *timer = glomp_checktimer(L, 1);
	delete timer;
	return 0;
}

int glomp_timer_start(lua_State *L) {
	Timer *timer = glomp_checktimer(L, 1);
	timer->start();
	return 0;
}

int glomp_timer_stop(lua_State *L) {
	Timer *timer = glomp_checktimer(L, 1);
	timer->stop();
	return 0;
}

int glomp_timer_elapsed(lua_State *L) {
	Timer *timer = glomp_checktimer(L, 1);
	lua_pushnumber(L, timer->elapsed());
	return 1;
}

int glomp_timer_reset(lua_State *L) {
	Timer *timer = glomp_checktimer(L, 1);
	timer->stop();
	timer->start();
	return 0;
}

static const struct luaL_Reg glomp_timer_main [] = {
	{"new", glomp_timer_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_timer_funcs [] = {
	{"start", glomp_timer_start},
	{"stop", glomp_timer_stop},
	{"elapsed", glomp_timer_elapsed},
	{"reset", glomp_timer_reset},
	{"__gc", glomp_timer_gc},
	{NULL, NULL}
};


int luaopen_timer(lua_State *L) {
	luaL_newmetatable(L, "glomp.timer");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_timer_funcs, 0);

	luaL_newlib(L, glomp_timer_main);
	lua_setglobal(L, "timer");
	return 1;
}

}
} /* namespace glomp */
