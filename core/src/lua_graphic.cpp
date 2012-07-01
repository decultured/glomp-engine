//
//  lua_graphic.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "lua_graphic.h"
#include <iostream>

namespace glomp {
namespace graphics {

#define glomp_checkgraphic(L, N) *(Graphic **)luaL_checkudata(L, N, "glomp.graphic")
    
int glomp_graphic_new(lua_State *L) {
    Graphic **new_graphic = (Graphic **)lua_newuserdata(L, sizeof(Graphic *));
    luaL_getmetatable(L, "glomp.image");
    lua_setmetatable(L, -2);
    
    *new_graphic = new Graphic();
    
    std::cout << "Graphic Created" << new_graphic;
    
    return 1;
}

int glomp_image_gc(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    std::cout << "Graphic Killed" << graphic;

    delete graphic;

    return 0;
}

//int glomp_image_load(lua_State *L) {
//    Graphic *graphic = glomp_checkgraphic(L, 1);
//    
//    const char *filename = luaL_checkstring(L, 2);
//    graphic->load(filename);
//    
//    return 0;
//}
//
//int glomp_image_get_id(lua_State *L) {
//    Image *image = glomp_checkimage(L, 1);
//    lua_pushnumber(L, image->get_id());
//    return 1;
//}
//
//int glomp_image_draw(lua_State *L) {
//    Image *image = glomp_checkimage(L, 1);
//    image->draw();
//    return 0;
//}

static const struct luaL_Reg glomp_graphic [] = {
    {"new", glomp_graphic_new},
    {NULL, NULL}
};

//    {"load", glomp_image_load},
//    {"get_id", glomp_image_get_id},
//    {"draw", glomp_image_draw},

static const struct luaL_Reg glomp_graphic_methods [] = {
    {"__gc", glomp_image_gc},
    {NULL, NULL}
};

int luaopen_graphic(lua_State *L) {
    luaL_newmetatable(L, "glomp.graphic");
    
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

//    Lua 5.2 version - changed backwards for compatibility with Lua Jit 1.X
//    luaL_setfuncs(L, glomp_graphic_funcs, 0);
//    luaL_newlib(L, glomp_graphic_main);
//    lua_setglobal(L, "image");

    luaL_register(L, NULL, glomp_graphic);
    luaL_register(L, "graphic", glomp_graphic);
    
    return 1;
}

}
}