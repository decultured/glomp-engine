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

int glomp_obj2d_rotate(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2)) {
		obj->rotation += luaL_checknumber(L, 2);
	}

	lua_pushnumber(L, obj->rotation);

	return 1;
}

int glomp_obj2d_translate(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
		obj->x += luaL_checknumber(L, 2);
		obj->y += luaL_checknumber(L, 3);
	}

	lua_pushnumber(L, obj->x);
	lua_pushnumber(L, obj->y);

	return 2;
}

int glomp_obj2d_scale(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
		obj->width *= luaL_checknumber(L, 2);
		obj->height *= luaL_checknumber(L, 3);
	}

	lua_pushnumber(L, obj->width);
	lua_pushnumber(L, obj->height);

	return 2;
}

int glomp_obj2d_rotation(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2)) {
		obj->rotation = luaL_checknumber(L, 2);
	}

	lua_pushnumber(L, obj->rotation);

	return 1;
}

int glomp_obj2d_position(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
		obj->x = luaL_checknumber(L, 2);
		obj->y = luaL_checknumber(L, 3);
	}

	lua_pushnumber(L, obj->x);
	lua_pushnumber(L, obj->y);

	return 2;
}

int glomp_obj2d_size(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
		obj->width = luaL_checknumber(L, 2);
		obj->height = luaL_checknumber(L, 3);
	}

	lua_pushnumber(L, obj->width);
	lua_pushnumber(L, obj->height);

	return 2;
}


static const struct luaL_Reg glomp_obj2d_main [] = {
	{"new", glomp_obj2d_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_obj2d_funcs [] = {
	{"set_texture_id", glomp_obj2d_set_texture_id},
	{"update", glomp_obj2d_update},
	{"render", glomp_obj2d_render},
	{"rotate", glomp_obj2d_rotate},
	{"translate", glomp_obj2d_translate},
	{"scale", glomp_obj2d_scale},
	{"rotation", glomp_obj2d_rotation},
	{"position", glomp_obj2d_position},
	{"size", glomp_obj2d_size},
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
