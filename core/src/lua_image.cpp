//
//  lua_image.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/7/12.
//
//

#include <string>
#include <iostream>
#include "lua_image.h"

namespace glomp {
    
#define glomp_checkimage(L, N) *(ofImage **)luaL_checkudata(L, N, "glomp.image")
    
    static int image_new(lua_State *L) {
        const char * filename = luaL_checkstring(L, 1);
        
        ofImage **image= (ofImage **)lua_newuserdata(L, sizeof(ofImage *));
        luaL_getmetatable(L, "glomp.image");
        lua_setmetatable(L, -2);
        
        *image= new ofImage();
        
        (*image)->loadImage(filename);
        
        return 1;
    }
    
    static int from_screen(lua_State *L) {
        int x = luaL_checkinteger(L, 1);
        int y = luaL_checkinteger(L, 2);
        int w = luaL_checkinteger(L, 3);
        int h = luaL_checkinteger(L, 4);
        
        ofImage **image= (ofImage **)lua_newuserdata(L, sizeof(ofImage *));
        luaL_getmetatable(L, "glomp.image");
        lua_setmetatable(L, -2);
        
        *image= new ofImage();
        
        (*image)->grabScreen(x, y, w, h);
        
        return 1;
    }
    
    static int image_gc(lua_State *L) {
        ofImage *image= glomp_checkimage(L, 1);
        
        delete image;
        
        return 0;
    }
    
    static int draw_image(lua_State *L) {
        ofImage *image= glomp_checkimage(L, 1);
        
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        
        if (lua_isnumber(L, 4) && lua_isnumber(L, 5)) {
            float w = lua_tonumber(L, 4);
            float h = lua_tonumber(L, 5);
            image->draw(x, y, w, h);
        }

        image->draw(x, y);
        
        return 0;
    }
    
    static int get_width(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        lua_pushnumber(L, image->getWidth());
        
        return 1;
    }
    
    static int get_height(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        lua_pushnumber(L, image->getHeight());
        
        return 1;
    }
    
    static int get_color_at(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        int x = luaL_checkinteger(L, 2);
        int y = luaL_checkinteger(L, 3);
        
        ofColor result = image->getColor(x, y);
        
        lua_pushnumber(L, result.r);
        lua_pushnumber(L, result.g);
        lua_pushnumber(L, result.b);
        lua_pushnumber(L, result.a);
        
        return 4;
    }
    
    static int mirror(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        bool vertical = lua_toboolean(L, 2);
        bool horizontal = lua_toboolean(L, 3);
        
        image->mirror(vertical, horizontal);
        
        return 0;
    }
    
    static int resize(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        bool w = lua_toboolean(L, 2);
        bool h = lua_toboolean(L, 3);
        
        image->resize(w, h);
        
        return 0;
    }
    
    static int crop(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);

        bool x = lua_toboolean(L, 2);
        bool y = lua_toboolean(L, 3);
        bool w = lua_toboolean(L, 4);
        bool h = lua_toboolean(L, 5);
        
        image->crop(x, y, w, h);
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_image[] = {
        {"new", image_new},
        {"from_screen", image_new},
        {NULL, NULL}
    };
    
    static const struct luaL_Reg glomp_image_methods [] = {
        {"draw", draw_image},
        {"get_width", get_width},
        {"get_height", get_height},
        {"get_color_at", get_color_at},
        {"mirror", mirror},
        {"resize", resize},
        {"crop", crop},
        {"__gc", image_gc},
        {NULL, NULL}
    };
    
    int luaopen_image(lua_State *L) {
        luaL_newmetatable(L, "glomp.image");
        
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        
        luaL_register(L, NULL, glomp_image_methods);
        luaL_register(L, "image", glomp_image);
        
        return 1;
    }
    
}