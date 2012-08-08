//
//  lua_image.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/7/12.
//
//

#ifndef glOMP_lua_image_h
#define glOMP_lua_image_h

#include "ofMain.h"

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glomp {
    
    int luaopen_image(lua_State *L);
    
}

#endif
