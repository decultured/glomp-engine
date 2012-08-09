//
//  lua_arduino.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#include "lua_arduino.h"

namespace glomp {
    
#define glomp_checkarduino(L, N) *(ofArduino **)luaL_checkudata(L, N, "glomp.arduino")
    
    static int arduino_new(lua_State *L) {
       
        ofArduino **arduino= (ofArduino **)lua_newuserdata(L, sizeof(ofArduino *));
        luaL_getmetatable(L, "glomp.arduino");
        lua_setmetatable(L, -2);
        
        *arduino = new ofArduino();
        
        return 1;
    }
    
    static int arduino_gc(lua_State *L) {
        ofArduino *arduino= glomp_checkarduino(L, 1);
        
        arduino->disconnect();
        
        delete arduino;
        
        return 0;
    }
        
    static const struct luaL_Reg glomp_arduino[] = {
        {"new", arduino_new},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg glomp_arduino_methods [] = {
        {"__gc", arduino_gc},
        {NULL, NULL}
    };
    
    int luaopen_arduino(lua_State *L) {
        luaL_newmetatable(L, "glomp.arduino");
        
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        
        luaL_register(L, NULL, glomp_arduino_methods);
        luaL_register(L, "arduino", glomp_arduino);
        
        return 1;
    }
}