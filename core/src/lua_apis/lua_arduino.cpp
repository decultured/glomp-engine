//
//  lua_arduino.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#include "lua_arduino.h"

namespace glOMP {
        
    static int lua_arduino_load(lua_State *L) {
        
        ofArduino **arduino= (ofArduino **)lua_newuserdata(L, sizeof(ofArduino *));
        luaL_getmetatable(L, "glOMP.arduino");
        lua_setmetatable(L, -2);
        
        *arduino = new ofArduino();
        
        return 1;
    }
    
    static int lua_arduino_gc(lua_State *L) {
        ofArduino *arduino= glomp_checkarduino(L, 1);
        
        arduino->disconnect();
        
        delete arduino;
        
        return 0;
    }
    
    static const struct luaL_Reg lua_arduino_methods[] = {
        {"load", lua_arduino_load},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg lua_arduino_metamethods [] = {
        {"__gc", lua_arduino_gc},
        {NULL, NULL}
    };
    
    void luaopen_arduino(lua_State *L) {
        register_metatable(L, "glOMP.arduino", lua_arduino_metamethods);
        register_module(L, "arduino", lua_arduino_methods);
    }
}
