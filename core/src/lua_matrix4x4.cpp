//
//  lua_matrix4x4.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/14/12.
//
//

#include "lua_matrix4x4.h"

namespace glomp {

static int lua_matrix4x4_create(lua_State *L) {
    ofMatrix4x4 **m4= (ofMatrix4x4 **)lua_newuserdata(L, sizeof(ofMatrix4x4 *));
    luaL_getmetatable(L, "glomp.matrix4x4");
    lua_setmetatable(L, -2);
    
    *m4 = new ofMatrix4x4();
    (*m4)->makeIdentityMatrix();
    
    return 1;
}

static int lua_matrix4x4_gc(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    delete m4;
    
    return 0;
}

static int lua_matrix4x4_copy_of(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    ofMatrix4x4 *m4_2 = glomp_checkmatrix4x4(L, 2);
    
    m4->set(*m4_2);
    
    return 0;
}

static int lua_matrix4x4_identity(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    m4->makeIdentityMatrix();
    
    return 0;
}
    
static int lua_matrix4x4_inverse(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    m4->makeInvertOf(*m4);
    
    return 1;
}

static int lua_matrix4x4_inverse_of(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    ofMatrix4x4 *m4_2 = glomp_checkmatrix4x4(L, 2);
    
    m4->makeInvertOf(*m4_2);
    
    return 1;
}

static int lua_matrix4x4_rotate(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    float angle = luaL_checknumber(L, 2);
    
    if (lua_gettop(L) > 1) {
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 2);
        m4->rotate(angle, x, y, z);
    } else {
        m4->rotate(angle, 0.0f, 0.0f, 1.0f);
    }
    
    return 0;
}

static int lua_matrix4x4_get_rotation(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    ofQuaternion quat = m4->getRotate();
    
    ofVec3f v3 = quat.getEuler();
    
    lua_pushnumber(L, v3.x);
    lua_pushnumber(L, v3.y);
    lua_pushnumber(L, v3.z);
    
    return 3;
}

static int lua_matrix4x4_translate(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0.0f;
    
    m4->translate(x, y, z);
    
    return 0;
}

static int lua_matrix4x4_get_translation(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    ofVec3f v3 = m4->getTranslation();
    
    lua_pushnumber(L, v3.x);
    lua_pushnumber(L, v3.y);
    lua_pushnumber(L, v3.z);
    
    return 3;
}

static int lua_matrix4x4_scale(lua_State *L) {
    ofMatrix4x4 *m4= glomp_checkmatrix4x4(L, 1);
    
    float x_scale = luaL_checknumber(L, 2);
    float y_scale = luaL_checknumber(L, 3);
    float z_scale = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 1.0f;
    
    m4->scale(x_scale, y_scale, z_scale);
    
    return 0;
}

static int lua_matrix4x4_get_scale(lua_State *L) {
    ofMatrix4x4 *m4= glomp_checkmatrix4x4(L, 1);
    
    ofVec3f v3 = m4->getScale();
    
    lua_pushnumber(L, v3.x);
    lua_pushnumber(L, v3.y);
    lua_pushnumber(L, v3.z);
    
    return 3;
}

static int lua_matrix4x4_transform(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    ofVec3f v3;
    
    v3.x = luaL_checknumber(L, 2);
    v3.y = luaL_checknumber(L, 3);
    v3.z = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0.0f;
    
    v3 = (*m4) * v3;
    
    lua_pushnumber(L, v3.x);
    lua_pushnumber(L, v3.y);
    lua_pushnumber(L, v3.z);
    
    return 3;
}
    
static int lua_matrix4x4_inv_transform(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    ofVec3f v3;
    
    ofMatrix4x4 inv;
    inv.getInverseOf(*m4);
    
    v3.x = luaL_checknumber(L, 2);
    v3.y = luaL_checknumber(L, 3);
    v3.z = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0.0f;
    
    v3 = inv * v3;
    
    lua_pushnumber(L, v3.x);
    lua_pushnumber(L, v3.y);
    lua_pushnumber(L, v3.z);
    
    return 3;
}
    
static int lua_matrix4x4_push(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    
    glPushMatrix();
    glMultMatrixf(m4->getPtr());
//    glLoadMatrixf(m4->getPtr());
    
    return 0;
}

static int lua_matrix4x4_pop(lua_State *L) {
    ofMatrix4x4 *m4 = glomp_checkmatrix4x4(L, 1);
    
    glPopMatrix();
    
    return 0;
}
    
static const struct luaL_Reg lua_matrix4x4_methods[] = {
    {"create", lua_matrix4x4_create},
    {NULL, NULL}
};

static const struct luaL_Reg lua_matrix4x4_metamethods [] = {
    {"copy_of", lua_matrix4x4_copy_of},
    {"identity", lua_matrix4x4_identity},
    {"inverse", lua_matrix4x4_inverse},
    {"inverse_of", lua_matrix4x4_inverse_of},
    {"rotate", lua_matrix4x4_rotate},
    {"get_rotation", lua_matrix4x4_get_rotation},
    {"translate", lua_matrix4x4_translate},
    {"get_translation", lua_matrix4x4_get_translation},
    {"scale", lua_matrix4x4_scale},
    {"get_scale", lua_matrix4x4_get_scale},
    {"transform", lua_matrix4x4_transform},
    {"inv_transform", lua_matrix4x4_inv_transform},
    {"push", lua_matrix4x4_push},
    {"pop", lua_matrix4x4_pop},
    {"__gc", lua_matrix4x4_gc},
    {NULL, NULL}
};

void luaopen_matrix4x4(lua_State *L) {
    register_metatable(L, "glomp.matrix4x4", lua_matrix4x4_metamethods);
    register_module(L, "matrix4x4", lua_matrix4x4_methods);
}

}

