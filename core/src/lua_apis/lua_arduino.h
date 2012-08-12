//
//  lua_arduino.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#ifndef __glOMP__lua_arduino__
#define __glOMP__lua_arduino__

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
        
    #define glomp_checkarduino(L, N) *(ofArduino **)luaL_checkudata(L, N, "glOMP.arduino")
        
    static int lua_arduino_load(lua_State *L);
    static int lua_arduino_gc(lua_State *L);
    
    void luaopen_arduino(lua_State *L);
}

#endif
