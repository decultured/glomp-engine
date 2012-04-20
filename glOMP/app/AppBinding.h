/*
 * AppBinding.h
 *
 *  Created on: Apr 10, 2012
 *      Author: jgraves
 */

#ifndef APPBINDING_H_
#define APPBINDING_H_

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#import "Window.h"


namespace glomp {
namespace app {

	int glomp_window_new(lua_State *L);
	int glomp_window_init(lua_State *L);
	int glomp_window_resize(lua_State *L);
	int glomp_window_shutdown(lua_State *L);
	int glomp_window_clearcolor(lua_State *L);
	int glomp_window_clear(lua_State *L);
	int glomp_window_update(lua_State *L);
	int luaopen_window (lua_State *L);
}
} /* namespace glomp */
#endif /* APPBINDING_H_ */
