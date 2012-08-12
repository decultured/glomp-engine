//
//  lua_util.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/11/12.
//
//

#ifndef glOMP_lua_util_h
#define glOMP_lua_util_h

#include <iostream>
#include <string>
#include <sstream>

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glOMP {

    void register_metatable(lua_State *L, const char *metatable_name, const luaL_Reg *l);
    void register_module(lua_State *L, const char *module_name, const luaL_Reg *l);
    
    void lua_print(lua_State * L, const char *message);
    void lua_print(lua_State * L, std::string &message);
    
    void lua_report_errors(lua_State *L, const char *message);
    
    int lua_set_path(lua_State *L, const char* path);
    
    bool lua_load_file(lua_State *L, const char *filename);
}

#endif
