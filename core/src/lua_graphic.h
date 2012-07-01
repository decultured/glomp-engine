//
//  lua_graphic.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_graphic_h
#define glOMP_lua_graphic_h

#include "graphic.h"

extern "C" {
    #include "lua.h"
    #include "luaconf.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

namespace glomp {
namespace graphics {

int glomp_graphic_new(lua_State *L);
int glomp_graphic_gc(lua_State *L);

int luaopen_graphic(lua_State *L);
    
}
}

#endif
