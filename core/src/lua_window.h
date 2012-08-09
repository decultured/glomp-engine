//
//  lua_window.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#ifndef __glOMP__lua_window__
#define __glOMP__lua_window__

#include "ofMain.h"

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glomp {
    
    int luaopen_window(lua_State *L);
    
}

#endif
