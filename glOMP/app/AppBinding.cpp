/*
 * AppBinding.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: jgraves
 */

#include "AppBinding.h"

extern "C" {
	#include "lua.h"
}

namespace glomp {
namespace app {

static int omp_window_init(lua_State *L)
{
	int width = lua_tonumber(L, 1);
	int height = lua_tonumber(L, 2);
	//init(width, height, 8, false);
	return 0;
}

static int omp_window_resize(lua_State *L)
{
	return 0;
}

} /* namespace app */
} /* namespace glomp */
