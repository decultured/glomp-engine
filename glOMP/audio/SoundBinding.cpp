/*
 * SoundBinding.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#include "SoundBinding.h"
#include <iostream>

namespace glomp {
namespace audio {

#define glomp_checksound(L, N) *(Sound **)luaL_checkudata(L, N, "glomp.sound")

int glomp_sound_new(lua_State *L) {
	Sound **new_sound = (Sound **)lua_newuserdata(L, sizeof(Sound *));
	luaL_getmetatable(L, "glomp.sound");
	lua_setmetatable(L, -2);

	*new_sound = new Sound();

	return 1;
}

int glomp_sound_gc(lua_State *L) {
	Sound *sound = glomp_checksound(L, 1);
	delete sound;
	return 0;
}

int glomp_sound_play(lua_State *L) {
	Sound *sound = glomp_checksound(L, 1);
	sound->play();
	return 0;
}

int glomp_sound_load_wav(lua_State *L) {
	Sound *sound = glomp_checksound(L, 1);

	const char *filename = luaL_checkstring(L, 2);
	sound->load_wav(filename);

	return 0;
}


static const struct luaL_Reg glomp_sound_main [] = {
	{"new", glomp_sound_new},
	{NULL, NULL}
};

static const struct luaL_Reg glomp_sound_funcs [] = {
	{"play", glomp_sound_play},
	{"load_wav", glomp_sound_load_wav},
	{"__gc", glomp_sound_gc},
	{NULL, NULL}
};


int luaopen_sound(lua_State *L) {
	luaL_newmetatable(L, "glomp.sound");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	luaL_setfuncs(L, glomp_sound_funcs, 0);
	luaL_newlib(L, glomp_sound_main);
	lua_setglobal(L, "sound");

	return 1;
}


} /* namespace audio */
} /* namespace glomp */
