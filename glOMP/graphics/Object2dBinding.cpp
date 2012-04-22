/*
 * Object2dBinding.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "Object2dBinding.h"
#include <iostream>

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

	return 0;
}

int glomp_obj2d_get_texture_id(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	lua_pushnumber(L, obj->get_texture_id());

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

int glomp_obj2d_apply_transform(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	obj->apply_transform();
	return 0;
}

int glomp_obj2d_remove_transform(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	obj->remove_transform();
	return 0;
}

int glomp_obj2d_draw(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	obj->draw();
	return 0;
}

int glomp_obj2d_make_polar(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);
	if (lua_isboolean(L, 2))
		obj->is_polar = lua_toboolean(L, 2);
	else
		std::cerr << "Parameter must be boolean\n";
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

int glomp_obj2d_texture_coords(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4) && lua_isnumber(L, 5)) {
		obj->tx = luaL_checknumber(L, 2);
		obj->ty = luaL_checknumber(L, 3);
		obj->tw = luaL_checknumber(L, 4);
		obj->th = luaL_checknumber(L, 5);
	}

	lua_pushnumber(L, obj->tx);
	lua_pushnumber(L, obj->ty);
	lua_pushnumber(L, obj->tw);
	lua_pushnumber(L, obj->th);

	return 4;
}

int glomp_obj2d_color(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4) && lua_isnumber(L, 5)) {
		obj->r = luaL_checknumber(L, 2);
		obj->g = luaL_checknumber(L, 3);
		obj->b = luaL_checknumber(L, 4);
		obj->a = luaL_checknumber(L, 5);
	}

	lua_pushnumber(L, obj->r);
	lua_pushnumber(L, obj->g);
	lua_pushnumber(L, obj->b);
	lua_pushnumber(L, obj->a);

	return 4;
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

int glomp_obj2d_center(lua_State *L) {
	Object2d *obj = glomp_checkobject2d(L, 1);

	if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
		obj->center_x = luaL_checknumber(L, 2);
		obj->center_y = luaL_checknumber(L, 3);
	}

	lua_pushnumber(L, obj->center_x);
	lua_pushnumber(L, obj->center_y);

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
	{"get_texture_id", glomp_obj2d_get_texture_id},
	{"make_polar", glomp_obj2d_make_polar},
	{"update", glomp_obj2d_update},
	{"render", glomp_obj2d_render},
	{"draw", glomp_obj2d_draw},
	{"color", glomp_obj2d_color},
	{"center", glomp_obj2d_center},
	{"texture_coords", glomp_obj2d_texture_coords},
	{"apply_transform", glomp_obj2d_apply_transform},
	{"remove_transform", glomp_obj2d_remove_transform},
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
