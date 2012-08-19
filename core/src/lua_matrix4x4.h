//
//  lua_matrix4x4.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/14/12.
//
//

#ifndef glOMP_lua_matrix4x4_h
#define glOMP_lua_matrix4x4_h

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {

#define glomp_checkmatrix4x4(L, N) *(ofMatrix4x4 **)luaL_checkudata(L, N, "glomp.matrix4x4")
    
    static int lua_matrix4x4_create(lua_State *L);
    static int lua_matrix4x4_gc(lua_State *L);
    
    void luaopen_matrix4x4(lua_State *L);

}

#endif
