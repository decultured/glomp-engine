//
//  lua_node.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/14/12.
//
//

#ifndef __glOMP__lua_node__
#define __glOMP__lua_node__

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
#define glomp_checknode(L, N) *(ofNode **)luaL_checkudata(L, N, "glomp.node")
    
    static int lua_node_create(lua_State *L);
    static int lua_node_gc(lua_State *L);
    
    void luaopen_node(lua_State *L);
    
}

#endif
