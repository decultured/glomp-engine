//
//  lua_image.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/7/12.
//
//

#include "lua_image.h"

namespace glOMP {
    
    static int lua_image_load(lua_State *L) {
        const char * filename = luaL_checkstring(L, 1);
        
        ofImage **image= (ofImage **)lua_newuserdata(L, sizeof(ofImage *));
        luaL_getmetatable(L, "glOMP.image");
        lua_setmetatable(L, -2);
        
        *image= new ofImage();
        
        (*image)->loadImage(filename);
        
        return 1;
    }
    
    static int lua_image_load_from_screen(lua_State *L) {
        int x = luaL_checkinteger(L, 1);
        int y = luaL_checkinteger(L, 2);
        int w = luaL_checkinteger(L, 3);
        int h = luaL_checkinteger(L, 4);
        
        ofImage **image= (ofImage **)lua_newuserdata(L, sizeof(ofImage *));
        luaL_getmetatable(L, "glOMP.image");
        lua_setmetatable(L, -2);
        
        *image= new ofImage();
        
        (*image)->grabScreen(x, y, w, h);
        
        return 1;
    }
    
    static int lua_image_gc(lua_State *L) {
        ofImage *image= glomp_checkimage(L, 1);
        
        delete image;
        
        return 0;
    }
    
    static int lua_image_draw(lua_State *L) {
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
    
    static int lua_image_draw_subsection(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float w = luaL_checknumber(L, 4);
        float h = luaL_checknumber(L, 5);
        float sx = luaL_checknumber(L, 6);
        float sy = luaL_checknumber(L, 7);
        float sw = luaL_checknumber(L, 8);
        float sh = luaL_checknumber(L, 9);
        
        image->drawSubsection(x, y, w, h, sx, sy, sw, sh);
        
        return 0;
    }
    
    static int lua_image_get_width(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        lua_pushnumber(L, image->getWidth());
        
        return 1;
    }
    
    static int lua_image_get_height(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        lua_pushnumber(L, image->getHeight());
        
        return 1;
    }
    
    static int lua_image_get_color_at(lua_State *L) {
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
    
    static int lua_image_mirror(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        bool vertical = lua_toboolean(L, 2);
        bool horizontal = lua_toboolean(L, 3);
        
        image->mirror(vertical, horizontal);
        
        return 0;
    }
    
    static int lua_image_resize(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        bool w = lua_toboolean(L, 2);
        bool h = lua_toboolean(L, 3);
        
        image->resize(w, h);
        
        return 0;
    }
    
    static int lua_image_crop(lua_State *L) {
        ofImage *image = glomp_checkimage(L, 1);
        
        bool x = lua_toboolean(L, 2);
        bool y = lua_toboolean(L, 3);
        bool w = lua_toboolean(L, 4);
        bool h = lua_toboolean(L, 5);
        
        image->crop(x, y, w, h);
        
        return 0;
    }
    
    static const struct luaL_Reg lua_image_methods[] = {
        {"load", lua_image_load},
        {"load_from_screen", lua_image_load_from_screen},
        {NULL, NULL}
    };
    
    static const struct luaL_Reg lua_image_metamethods [] = {
        {"draw", lua_image_draw},
        {"draw_subsection", lua_image_draw_subsection},
        {"get_width", lua_image_get_width},
        {"get_height", lua_image_get_height},
        {"get_color_at", lua_image_get_color_at},
        {"mirror", lua_image_mirror},
        {"resize", lua_image_resize},
        {"crop", lua_image_crop},
        {"__gc", lua_image_gc},
        {NULL, NULL}
    };
    
    void luaopen_image(lua_State *L) {
        register_metatable(L, "glOMP.image", lua_image_metamethods);
        register_module(L, "image", lua_image_methods);
    }
    
}
