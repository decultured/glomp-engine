/*
 * Object2dBinding.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "Object2dBinding.h"

namespace glomp {
namespace graphics {

#define glomp_checkobject2d(L, N) *(Object2d **)luaL_checkudata(L, N, "glomp.object2d")

int glomp_obj2d_new(lua_State *L) {
	Object2d **new_obj = (Object2d **)lua_newuserdata(L, sizeof(Object2d *));
	luaL_getmetatable(L, "glomp.object2d");
	lua_setmetatable(L, -2);

	*new_obj = new Object2d();

	return 1;
}

int glomp_obj2d_gc(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	delete obj;
	return 0;
}

int glomp_obj2d_set_texture_id(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	unsigned int texture_id = luaL_checknumber(L, 2);
	obj->set_texture_id(texture_id);

	return 1;
}

int glomp_obj2d_update(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	float time_elapsed = luaL_checknumber(L, 2);
	obj->update(time_elapsed);
	return 0;
}

int glomp_obj2d_render(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	obj->render();
	return 0;
}

static const struct luaL_Reg glomp_obj2d_main [] = {
	{"new", glomp_obj2d_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_obj2d_funcs [] = {
	{"set_texture_id", glomp_obj2d_set_texture_id},
	{"update", glomp_obj2d_update},
	{"render", glomp_obj2d_render},
	{"__gc", glomp_obj2d_gc},
	{NULL, NULL}
};


int luaopen_obj2d(lua_State *L) {
	luaL_newmetatable(L, "glomp.object2d");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_obj2d_funcs, 0);

	luaL_newlib(L, glomp_obj2d_main);
	lua_setglobal(L, "object2d");
	return 1;
}

} /* namespace graphics */
} /* namespace glomp */
