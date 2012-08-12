//
//  lua_directory.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/10/12.
//
//

#ifndef __glOMP__lua_directory__
#define __glOMP__lua_directory__

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
    
    static int lua_directory_is_directory(lua_State *L);
    static int lua_directory_list(lua_State *L);
    static int lua_directory_list_full(lua_State *L);
    static int lua_directory_num_files(lua_State *L);
    static int lua_directory_is_empty(lua_State *L);
    static int lua_directory_is_hidden(lua_State *L);
    static int lua_directory_create(lua_State *L);
    
    void luaopen_directory(lua_State *L);
    
}

#endif
