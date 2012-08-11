//
//  lua_util.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/11/12.
//
//

#ifndef glOMP_lua_util_h
#define glOMP_lua_util_h

extern "C" {
#include "lua.h"
#include "luaconf.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace glOMP {

    void register_metatable(lua_State *L, const char *metatable_name, const luaL_Reg *l) {
        luaL_newmetatable(L, metatable_name);
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, l);
    }

    void register_module(lua_State *L, const char *module_name, const luaL_Reg *l) {
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
    
}

#endif
