//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_wrapper.h"

namespace glomp {
namespace lua {

    static int l_print(lua_State* L) {
        int nargs = lua_gettop(L);
        
        for (int i=1; i <= nargs; i++) {
            if (lua_isstring(L, i)) {
                std::cout << lua_tostring(L, i);
            }
            else {
                /* Do something with non-strings? */
            }
        }
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



LuaWrapper::LuaWrapper() {
    L = NULL;
}

LuaWrapper::~LuaWrapper() {
    shutdown();
}
    
void LuaWrapper::init() {
    shutdown();

    L = lua_open();
    luaL_openlibs(L);
    luaopen_luaprintlib(L)
}

void LuaWrapper::shutdown() {
    if (!L)
        return;
    
    lua_close(L);
    L = NULL;
}
    
void LuaWrapper::load_file(const char *filename) {
    int s = luaL_loadfile(L, filename);
    if ( s==0 ) {
        s = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    report_errors(L, s);
}
    
void LuaWrapper::report_errors(lua_State *L, int status)
{
    if ( status!=0 ) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;

        lua_pop(L, 1);
    }
}
    
}
}