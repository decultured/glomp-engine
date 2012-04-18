/*
 * TimerBinding.h
 *
 *  Created on: Apr 17, 2012
 *      Author: jgraves
 */

#ifndef TIMERBINDING_H_
#define TIMERBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "Timer.h"

namespace glomp {
namespace util {

	int glomp_timer_new(lua_State *L);
	int glomp_timer_gc(lua_State *L);

	int glomp_timer_start(lua_State *L);
	int glomp_timer_stop(lua_State *L);
	int glomp_timer_elapsed(lua_State *L);
	int glomp_timer_reset(lua_State *L);

	int luaopen_timer(lua_State *L);
}
} /* namespace glomp */
#endif /* TIMERBINDING_H_ */
