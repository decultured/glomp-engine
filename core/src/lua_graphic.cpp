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
    
int graphic_new(lua_State *L) {
    Graphic **new_graphic = (Graphic **)lua_newuserdata(L, sizeof(Graphic *));
    luaL_getmetatable(L, "glomp.graphic");
    lua_setmetatable(L, -2);
    
    *new_graphic = new Graphic();
    
    std::cout << "Graphic Created: " << *new_graphic << std::endl;
    
    return 1;
}

int graphic_gc(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    std::cout << "Graphic Killed: " << graphic << std::endl;

    delete graphic;

    return 0;
}

int graphic_width(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);
    
    if (lua_isnumber(L, 2))
        graphic->width(luaL_checknumber(L, 2));

    lua_pushnumber(L, graphic->width());
    
    return 1;
}

int graphic_height(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2))
        graphic->height(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->height());

    return 1;
}

int graphic_size(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
        graphic->width(luaL_checknumber(L, 2));
        graphic->height(luaL_checknumber(L, 3));
    }
    
    lua_pushnumber(L, graphic->width());
    lua_pushnumber(L, graphic->height());
    
    return 2;
}

int graphic_x(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);
    
    if (lua_isnumber(L, 2))
        graphic->x(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->x());

    return 1;
}

int graphic_y(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2))
        graphic->y(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->y());
    
    return 1;
}

int graphic_position(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);
    
    if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
        graphic->x(luaL_checknumber(L, 2));
        graphic->y(luaL_checknumber(L, 3));
    }
    
    lua_pushnumber(L, graphic->x());
    lua_pushnumber(L, graphic->y());

    return 2;
}

int graphic_rotation(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2))
        graphic->rotation(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->rotation());
    
    return 1;
}

int graphic_scale_x(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2))
        graphic->scale_x(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->scale_x());
    
    return 1;
}

int graphic_scale_y(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);
    
    if (lua_isnumber(L, 2))
        graphic->scale_y(luaL_checknumber(L, 2));
    
    lua_pushnumber(L, graphic->scale_y());

    return 1;
}

int graphic_scale(lua_State *L) {
    Graphic *graphic = glomp_checkgraphic(L, 1);

    if (lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
        graphic->scale_x(luaL_checknumber(L, 2));
        graphic->scale_y(luaL_checknumber(L, 3));
    }
    
    lua_pushnumber(L, graphic->scale_x());
    lua_pushnumber(L, graphic->scale_y());
    
    return 2;
}


static const struct luaL_Reg glomp_graphic [] = {
    {"new", graphic_new},
    {NULL, NULL}
};


static const struct luaL_Reg glomp_graphic_methods [] = {
    {"height", graphic_height},
    {"width", graphic_width},
    {"size", graphic_size},
    {"x", graphic_x},
    {"y", graphic_y},
    {"position", graphic_position},
    {"rotation", graphic_rotation},
    {"scale_x", graphic_scale_x},
    {"scale_x", graphic_scale_y},
    {"scale", graphic_scale},
    {"__gc", graphic_gc},
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

    luaL_register(L, NULL, glomp_graphic_methods);
    luaL_register(L, "graphic", glomp_graphic);
    
    return 1;
}

}
}