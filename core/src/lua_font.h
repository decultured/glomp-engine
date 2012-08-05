//
//  lua_font.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_font_h
#define glOMP_lua_font_h

#include "ofMain.h"

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glomp {
    
    int luaopen_font(lua_State *L);
    
}


#endif
