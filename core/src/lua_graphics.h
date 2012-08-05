//
//  lua_graphics.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_gl_h
#define glOMP_lua_gl_h

#include "ofMain.h"

extern "C" {
    #include "lua.h"
    #include "luaconf.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

namespace glomp {
    
    int luaopen_graphics(lua_State *L);
    
}


#endif
