//
//  lua_print.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_print_h
#define glOMP_lua_print_h

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace glomp {
namespace lua {

void lua_print(lua_State *L, const char *message);
static int l_print(lua_State* L);
extern int luaopen_luaprintlib(lua_State *L);
    
}
}
        
#endif
