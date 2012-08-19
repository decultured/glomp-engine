//
//  lua_node.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/14/12.
//
//

#include "lua_node.h"

namespace glomp {
    
    static int lua_node_create(lua_State *L) {
        ofNode **node= (ofNode **)lua_newuserdata(L, sizeof(ofNode *));
        luaL_getmetatable(L, "glomp.node");
        lua_setmetatable(L, -2);
        
        *node = new ofNode();

        return 1;
    }
    
    static int lua_node_gc(lua_State *L) {
        ofNode *node = glomp_checknode(L, 1);
        
        delete node;
        
        return 0;
    }
    
    static int lua_node_rotate(lua_State *L) {
        ofNode *node = glomp_checknode(L, 1);
        
        float angle = luaL_checknumber(L, 2);
        
        if (lua_gettop(L) > 1) {
            float x = luaL_checknumber(L, 2);
            float y = luaL_checknumber(L, 2);
            float z = luaL_checknumber(L, 2);
            node->rotate(angle, x, y, z);
        } else {
            node->rotate(angle, 0.0f, 0.0f, 1.0f);
        }
        
        return 0;
    }
    
    static int lua_node_translate(lua_State *L) {
        ofNode *node = glomp_checknode(L, 1);
        
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0.0f;
        
        node->move(x, y, z);
        
        return 0;
    }
    
    static int lua_node_set_scale(lua_State *L) {
        ofNode *node= glomp_checknode(L, 1);
        
        float x_scale = luaL_checknumber(L, 2);
        float y_scale = luaL_checknumber(L, 3);
        float z_scale = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 1.0f;
        
        node->setScale(x_scale, y_scale, z_scale);
        
        return 0;
    }
    
    static const struct luaL_Reg lua_node_methods[] = {
        {"create", lua_node_create},
        {NULL, NULL}
    };
    
    static const struct luaL_Reg lua_node_metamethods [] = {
        {"rotate", lua_node_rotate},
        {"translate", lua_node_translate},
        {"set_scale", lua_node_set_scale},
        {"__gc", lua_node_gc},
        {NULL, NULL}
    };
    
    void luaopen_node(lua_State *L) {
        register_metatable(L, "glomp.node", lua_node_metamethods);
        register_module(L, "node", lua_node_methods);
    }
    
}

