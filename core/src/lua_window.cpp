//
//  lua_window.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#include "lua_window.h"

namespace glomp {
    
    static int set_fullscreen(lua_State *L) {
        const char *url = luaL_checkstring(L, 1);
        
        bool fullscreen = lua_toboolean(L, 2);
        
        ofSetFullscreen(fullscreen);
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_window[] = {
        {"set_fullscreen", set_fullscreen},
        {NULL, NULL}
    };
    
    int luaopen_window(lua_State *L) {
        luaL_register(L, "window", glomp_window);
        return 1;
    }
}