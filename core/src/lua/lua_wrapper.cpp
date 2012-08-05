//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//
#include "lua_wrapper.h"
#include "lua_print.h"
#include "lua_marshal.h"

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
    luaopen_marshal(L);
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

bool LuaWrapper::load_file(const char *filename) {
    // TODO : Change to direct lua dofile call?
    // Would have to wrap dofile from c at that point
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
        lua_pop(L, 1);
        return false;
    }
    return true;
}
    
void LuaWrapper::report_errors(lua_State *L, const char *message)
{
    std::ostringstream str_stream;
    str_stream << "Error: " << message << ":" << std::endl 
                            << "     " << lua_tostring(L, -1);

    print(str_stream.str().c_str());
}

void LuaWrapper::print(std::string &message) {
    print(message.c_str());
}

void LuaWrapper::print(const char *message) {
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

void LuaWrapper::update(double frame_time) {
    lua_getglobal(L, "_glomp_update");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, frame_time);

    if (lua_pcall(L, 1, 0, 0) != 0) {
        report_errors(L, "_glomp_update");
        return;
    }
}

       
}