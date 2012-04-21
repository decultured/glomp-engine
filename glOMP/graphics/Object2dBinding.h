/*
 * Object2dBinding.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef OBJECT2DBINDING_H_
#define OBJECT2DBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "Object2d.h"

namespace glomp {
namespace graphics {

int glomp_obj2d_new(lua_State *L);
int glomp_obj2d_gc(lua_State *L);

int glomp_obj2d_load(lua_State *L);
int glomp_obj2d_set_texture_id(lua_State *L);
int glomp_obj2d_update(lua_State *L);
int glomp_obj2d_render(lua_State *L);

int luaopen_obj2d(lua_State *L);

} /* namespace graphics */
} /* namespace glomp */
#endif /* OBJECT2DBINDING_H_ */
