/*
 * InputBinding.h
 *
 *  Created on: Apr 18, 2012
 *      Author: jgraves
 */

#ifndef INPUTBINDING_H_
#define INPUTBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

namespace glomp {
namespace input {

int glomp_input_new(lua_State *L);
int glomp_input_gc(lua_State *L);

int glomp_input_key_state(lua_State *L);
int glomp_input_mouse_button_state(lua_State *L);

int glomp_input_add_trigger(lua_State *L);
int glomp_input_add_listener(lua_State *L);
int glomp_input_update(lua_State *L);

int luaopen_input (lua_State *L);

}
} /* namespace glomp */
#endif /* INPUTBINDING_H_ */
