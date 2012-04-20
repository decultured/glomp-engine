/*
 * AudioBinding.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "AudioBinding.h"

namespace glomp {
namespace audio {

#define glomp_checkaudio(L, N) *(Audio **)luaL_checkudata(L, N, "glomp.audio")

int glomp_audio_new(lua_State *L) {
	Audio **new_audio = (Audio**)lua_newuserdata(L, sizeof(Audio *));
	luaL_getmetatable(L, "glomp.audio");
	lua_setmetatable(L, -2);

	*new_audio = new Audio();

	return 1;
}

int glomp_audio_gc(lua_State *L) {
	Audio *audio = glomp_checkaudio(L, 1);
	delete audio;
	return 0;
}

static const struct luaL_Reg glomp_audio_main [] = {
	{"new", glomp_audio_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_audio_funcs [] = {
	{"__gc", glomp_audio_gc},
	{NULL, NULL}
};

int luaopen_audio(lua_State *L) {
	luaL_newmetatable(L, "glomp.audio");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_audio_funcs, 0);

	luaL_newlib(L, glomp_audio_main);
	lua_setglobal(L, "audio");
	return 1;
}

} /* namespace audio */
} /* namespace glomp */
