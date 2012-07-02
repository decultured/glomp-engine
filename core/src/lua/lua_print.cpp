//
//  lua_print.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_print.h"

namespace glomp {
namespace lua {

void lua_print(lua_State *L, const char *message) {
    lua_getglobal(L, "print");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }

    lua_pushstring(L, message);
    
    if (lua_pcall(L, 1, 0, 0) != 0) {
        std::cout << "error calling lua print: %s\n" << lua_tostring(L, -1) << std::endl;
        return;
    }
}

static int l_print(lua_State* L) {
    int nargs = lua_gettop(L);
    
    for (int i=1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            std::cout << lua_tostring(L, i) << " ";
        }
        else {
            /* Do something with non-strings? */
        }
    }
    std::cout << std::endl;
    return 0;
}

static const struct luaL_reg printlib [] = {
    {"print", l_print},
    {NULL, NULL}
};

extern int luaopen_luaprintlib(lua_State *L)
{
    lua_getglobal(L, "_G");
    luaL_register(L, NULL, printlib);
    lua_pop(L, 1);
}
    
}
}