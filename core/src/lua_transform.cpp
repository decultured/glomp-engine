//
//  lua_transform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>

#include "lua_transform.h"
#include <iostream>

namespace glomp {
        
    #define glomp_checktransform(L, N) *(Transform **)luaL_checkudata(L, N, "glomp.transform")
    
    int transform_new(lua_State *L) {
        Transform **new_transform= (Transform **)lua_newuserdata(L, sizeof(Transform *));
        luaL_getmetatable(L, "glomp.transform");
        lua_setmetatable(L, -2);
        
        *new_transform= new Transform();
        
        std::cout << "Transform Created: " << *new_transform<< std::endl;
        
        return 1;
    }
    
    int transform_gc(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        std::cout << "Transform Killed: " << transform<< std::endl;
        
        delete transform;
        
        return 0;
    }
    
    int transform_x(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2))
            transform->x = luaL_checknumber(L, 2);
        
        lua_pushnumber(L, transform->x);
        
        return 1;
    }
    
    int transform_y(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2))
            transform->y= luaL_checknumber(L, 2);
        
        lua_pushnumber(L, transform->y);
        
        return 1;
    }
    
    int transform_position(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
            transform->x = luaL_checknumber(L, 2);
            transform->y = luaL_checknumber(L, 3);
        }
        
        lua_pushnumber(L, transform->x);
        lua_pushnumber(L, transform->y);
        
        return 2;
    }
    
    int transform_rotation(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2))
            transform->rotation = luaL_checknumber(L, 2);
        
        lua_pushnumber(L, transform->rotation);
        
        return 1;
    }
    
    int transform_scale_x(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2))
            transform->scale_x = luaL_checknumber(L, 2);
        
        lua_pushnumber(L, transform->scale_x);
        
        return 1;
    }
    
    int transform_scale_y(lua_State *L) {
        Transform *transform= glomp_checktransform(L, 1);
        
        if (lua_isnumber(L, 2))
            transform->scale_y = luaL_checknumber(L, 2);
        
        lua_pushnumber(L, transform->scale_y);
        
        return 1;
    }
    
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
    
    int luaopen_transform(lua_State *L) {
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