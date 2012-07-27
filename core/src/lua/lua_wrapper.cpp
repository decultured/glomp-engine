//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include <string>
#include "lua_wrapper.h"
#include "lua_print.h"

namespace glomp {

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
    luaopen_luaprintlib(L);
}

void LuaWrapper::shutdown() {
    if (!L)
        return;
    
    lua_close(L);
    L = NULL;
}
    
int LuaWrapper::set_lua_path(const char* path)  
{
    std::string new_path;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
    new_path = lua_tostring( L, -1 ); // grab path string from top of stack
    new_path = new_path + ";"; // do your path magic here
    new_path = new_path + path;
    new_path = new_path + "?.lua";
    lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( L, new_path.c_str()); // push the new one
    lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( L, 1 ); // get rid of package table from top of stack
    lua_pushstring(L, path);
    lua_setglobal(L, "LUA_PATH");
    return 0; // all done!
}

void LuaWrapper::error (lua_State *L, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
//    lua_close(L);
//    this->L = NULL;
//    exit(EXIT_FAILURE);
}


bool LuaWrapper::load_file(const char *filename) {
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
        std::cout << "### cannot run config. file:" << std::endl 
                    << "###     " << lua_tostring(L, -1);
        lua_pop(L, 1);
        
        return false;
    }
    return true;
}

    
void LuaWrapper::report_errors(lua_State *L, int status)
{
    std::cout << "Errors Found: " << status;
    if ( status!=0 ) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;

        lua_pop(L, 1);
    }
}

void LuaWrapper::print(const char *message) {
    if (L) lua_print(L, message);
}
       
}