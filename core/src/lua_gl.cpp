//
//  lua_gl.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_gl.h"

namespace glomp {
    
#define glomp_checktransform(L, N) *(Transform **)luaL_checkudata(L, N, "glomp.transform")
    
    int transform_scale(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
            transform->scale_x = luaL_checknumber(L, 2);
            transform->scale_y = luaL_checknumber(L, 3);
        }
        
        lua_pushnumber(L, transform->scale_x);
        lua_pushnumber(L, transform->scale_y);
        
        return 2;
    }
    
    static const struct luaL_Reg glomp_transform[] = {
        {"new", transform_new},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg glomp_transform_methods [] = {
        {"x", transform_x},
        {"y", transform_y},
        {"position", transform_position},
        {"rotation", transform_rotation},
        {"scale_x", transform_scale_x},
        {"scale_x", transform_scale_y},
        {"scale", transform_scale},
        {"__gc", transform_gc},
        {NULL, NULL}
    };
    
    int luaopen_gl(lua_State *L) {
        luaL_newmetatable(L, "glomp.transform");
        
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        
        //    Lua 5.2 version - changed backwards for compatibility with Lua Jit 1.X
        //    luaL_setfuncs(L, glomp_transform_funcs, 0);
        //    luaL_newlib(L, glomp_transform_main);
        //    lua_setglobal(L, "image");
        
        luaL_register(L, NULL, glomp_transform_methods);
        luaL_register(L, "transform", glomp_transform);
        
        return 1;
    }
    
}