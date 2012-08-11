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

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glomp {
    
    static int lua_directory_is_directory(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        
        ofDirectory dir(path);
        
        lua_pushboolean(L, dir.isDirectory());
        
        return 1;
    }
    
    static int lua_directory_list_contents(lua_State *L) {
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
    
    static int lua_directory_list_contents_full(lua_State *L) {
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
    /*
     static int lua_directory_can_read(lua_State *L) {
     const char *path = luaL_checkstring(L, 1);
     
     ofDirectory dir(path);
     
     lua_pushboolean(L, dir.canRead());
     
     return 1;
     }
     
     static int lua_directory_can_execute(lua_State *L) {
     const char *path = luaL_checkstring(L, 1);
     
     ofDirectory dir(path);
     
     lua_pushboolean(L, dir.canExecute());
     
     return 1;
     }
     
     static int lua_directory_can_write(lua_State *L) {
     const char *path = luaL_checkstring(L, 1);
     
     ofDirectory dir(path);
     
     lua_pushboolean(L, dir.canWrite());
     
     return 1;
     }
     */
    
    static int lua_directory_create(lua_State *L) {
        const char *path = luaL_checkstring(L, 1);
        bool relative = lua_toboolean(L, 2);
        
        ofDirectory dir;
        
        dir.createDirectory(path, relative);
        
        lua_pushboolean(L, dir.isHidden());
        
        return 1;
    }
    
    /*
     {"can_read", lua_directory_can_read},
     {"can_execute", lua_directory_can_execute},
     {"can_write", lua_directory_can_write},
     */
    
    static const struct luaL_Reg lua_directory_methods[] = {
        {"is_directory", lua_directory_is_directory},
        {"list", lua_directory_list_contents},
        {"list_full", lua_directory_list_contents_full},
        {"num_files", lua_directory_num_files},
        {"is_empty", lua_directory_is_empty},
        {"is_hidden", lua_directory_is_hidden},
        {"create", lua_directory_create},
        {NULL, NULL}
    };
    
    void register_glomp_module(lua_State *L, const luaL_Reg *l, const char *module_name) {
        lua_getglobal(L, "glOMP");
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);
        }
        
        lua_newtable(L);
        
        for (; l->name; l++) {
            lua_pushcclosure(L, l->func, 0);
            lua_setfield(L, -2, l->name);
            std::cout << l->name;
        }
        
        lua_setfield(L, -2, module_name);
        lua_setglobal(L, "glOMP");
        
        return 0;
    }
    
    void luaopen_directory(lua_State *L) {
        register_glomp_module(L, lua_directory_methods, "directory");
    }
    
}

#endif
