/*
 * SoundBinding.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef SOUNDBINDING_H_
#define SOUNDBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "Sound.h"

namespace glomp {
namespace audio {

int glomp_sound_new(lua_State *L);
int glomp_sound_gc(lua_State *L);

int glomp_sound_play(lua_State *L);
int glomp_sound_load_wav(lua_State *L);

int luaopen_sound(lua_State *L);

} /* namespace audio */
} /* namespace glomp */
#endif /* SOUNDBINDING_H_ */
