/*
 * AudioBinding.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef AUDIOBINDING_H_
#define AUDIOBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "Audio.h"

namespace glomp {
namespace audio {

int glomp_audio_new(lua_State *L);
int glomp_audio_gc(lua_State *L);

int luaopen_audio(lua_State *L);

} /* namespace audio */
} /* namespace glomp */
#endif /* AUDIOBINDING_H_ */
