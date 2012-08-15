//
//  lua_directory.cpp
//  glomp
//
//  Created by Jeffrey Graves on 8/10/12.
//
//

#include "lua_directory.h"

namespace glomp {
    
    static int lua_directory_is_directory(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir(path);
        
        lua_pushboolean(L, dir.isDirectory());
        
        return 1;
    }
    
    static int lua_directory_list(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir;
        dir.listDir(path);
        
        int num_files=(int)dir.size();
        lua_createtable(L, num_files, 0);
        
        for (int i=0; i< num_files; i++) {
            lua_pushstring(L, dir.getName(i).c_str());
            lua_rawseti (L, -2, i);
        }
        
        return 1;
    }
    
    static int lua_directory_list_full(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir;
        dir.listDir(path);
        
        int num_files=(int)dir.size();
        lua_createtable(L, num_files, 0);
        
        for (int i=0; i< num_files; i++) {
            lua_pushstring(L, dir.getPath(i).c_str());
            lua_rawseti (L, -2, i);
        }
        
        return 1;
    }
    
    static int lua_directory_num_files(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir(path);
        
        lua_pushnumber(L, dir.size());
        
        return 1;
    }
    
    static int lua_directory_is_empty(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir;
        
        lua_pushboolean(L, dir.isDirectoryEmpty(path));
        
        return 1;
    }
    
    static int lua_directory_is_hidden(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir(path);
        
        lua_pushboolean(L, dir.isHidden());
        
        return 1;
    }
    
    static int lua_directory_create(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        bool relative = lua_toboolean(L, 2);
        
        ofDirectory dir;
        
        dir.createDirectory(path, relative);
        
        lua_pushboolean(L, dir.isHidden());
        
        return 1;
    }
    
    static const struct luaL_Reg lua_directory_methods[] = {
        {"is_directory", lua_directory_is_directory},
        {"list", lua_directory_list},
        {"list_full", lua_directory_list_full},
        {"num_files", lua_directory_num_files},
        {"is_empty", lua_directory_is_empty},
        {"is_hidden", lua_directory_is_hidden},
        {"create", lua_directory_create},
        {NULL, NULL}
    };
    
    void luaopen_directory(lua_State *L) {
        register_module(L, "directory", lua_directory_methods);
    }
}
