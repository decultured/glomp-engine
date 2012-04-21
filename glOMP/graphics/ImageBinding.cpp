/*
 * ImageBinding.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "ImageBinding.h"

namespace glomp {
namespace graphics {

#define glomp_checkimage(L, N) *(Image **)luaL_checkudata(L, N, "glomp.image")

int glomp_image_new(lua_State *L) {
	Image **new_image = (Image **)lua_newuserdata(L, sizeof(Image *));
	luaL_getmetatable(L, "glomp.image");
	lua_setmetatable(L, -2);

	*new_image = new Image();

	return 1;
}

int glomp_image_gc(lua_State *L) {
	Image *image = glomp_checkimage(L, 1);
	delete image;
	return 0;
}

int glomp_image_load(lua_State *L) {
	Image *image = glomp_checkimage(L, 1);

	const char *filename = luaL_checkstring(L, 2);
	image->load(filename);

	return 0;
}

int glomp_image_get_id(lua_State *L) {
	Image *image = glomp_checkimage(L, 1);
	lua_pushnumber(L, image->get_id());
	return 1;
}

int glomp_image_draw(lua_State *L) {
	Image *image = glomp_checkimage(L, 1);
	image->draw();
	return 0;
}

static const struct luaL_Reg glomp_image_main [] = {
	{"new", glomp_image_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_image_funcs [] = {
	{"load", glomp_image_load},
	{"get_id", glomp_image_get_id},
	{"draw", glomp_image_draw},
	{"__gc", glomp_image_gc},
	{NULL, NULL}
};


int luaopen_image(lua_State *L) {
	luaL_newmetatable(L, "glomp.image");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_image_funcs, 0);

	luaL_newlib(L, glomp_image_main);
	lua_setglobal(L, "image");
	return 1;
}

} /* namespace graphics */
} /* namespace glomp */
