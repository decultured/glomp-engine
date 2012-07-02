//
//  lua_app.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_app_h
#define glOMP_lua_app_h

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace glomp {
namespace lua {
            
static int l_terminate(lua_State* L);
extern int luaopen_app(lua_State *L);
   
    
}
}

#endif
