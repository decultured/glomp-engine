//
//  lua_arduino.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#ifndef __glOMP__lua_arduino__
#define __glOMP__lua_arduino__

#include "ofMain.h"

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glomp {
    
    int luaopen_arduino(lua_State *L);
    
}

#endif
