/*
 * ImageBinding.h
 *
 *  Created on: Apr 20, 2012
 *      Author: jgraves
 */

#ifndef IMAGEBINDING_H_
#define IMAGEBINDING_H_

extern "C" {
	#include "lua.h"
	#include "luaconf.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "Image.h"

namespace glomp {
namespace graphics {

int glomp_image_new(lua_State *L);
int glomp_image_gc(lua_State *L);

int glomp_image_load(lua_State *L);
int glomp_image_get_id(lua_State *L);
int glomp_image_draw(lua_State *L);

int luaopen_image(lua_State *L);

} /* namespace graphics */
} /* namespace glomp */
#endif /* IMAGEBINDING_H_ */
