//
//  lua_font.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <string>
#include <iostream>
#include "lua_font.h"

namespace glomp {

#define glomp_checkfont(L, N) *(ofTrueTypeFont **)luaL_checkudata(L, N, "glomp.font")
    
    static int font_new(lua_State *L) {
        std::string filename = luaL_checkstring(L, 1);
        int fontsize = luaL_checkint(L, 2);
        bool antialiased = lua_toboolean(L, 3);
        bool full_char_set = lua_toboolean(L, 4);
        bool make_contours = lua_toboolean(L, 5);
        float simplify_amount = luaL_checknumber(L, 6);
        int dpi = luaL_checkint(L, 7);
        
        ofTrueTypeFont *new_font= *(ofTrueTypeFont **)lua_newuserdata(L, sizeof(ofTrueTypeFont *));
        luaL_getmetatable(L, "glomp.font");
        lua_setmetatable(L, -2);
        
        new_font= new ofTrueTypeFont();

        new_font->loadFont(filename.c_str(), fontsize, 
                        antialiased, full_char_set,
                        make_contours, simplify_amount, dpi);
        
        // std::cout << "Font Created: " << *new_transform<< std::endl;
        
        return 1;
    }
    
    static int font_gc(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        // std::cout << "Font Killed: " << transform << std::endl;
        
        delete font;
        
        return 0;
    }
    
    static int set_line_height(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);

        float line_height = luaL_checknumber(L, 1);
        
        new_font->setLineHeight(line_height);
        
        return 0;
    }
    
    static int set_letter_spacing(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        float letter_spacing = luaL_checknumber(L, 1);
        
        new_font->setLetterSpacing(letter_spacing);
        
        return 0;
    }
    
    static int set_space_size(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        float space_size = luaL_checknumber(L, 1);
        
        new_font->setSpaceSize(space_size);
        
        return 0;
    }
    
    static int set_global_dpi(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        int dpi = luaL_checkint(L, 1);
        
        new_font->setGlobalDpi(dpi);
        
        return 0;
    }
    
    static int get_string_height(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 1);
        
        float height = new_font->stringHeight(out);
        lua_pushnumber(L, height);
        
        return 1;
    }
    
    static int get_string_width(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 1);
        
        float width = new_font->stringHeight(out);
        lua_pushnumber(L, width);
        
        return 1;
    }

    static int get_line_height(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        float height = new_font->getLineHeight();
        lua_pushnumber(L, height);
        
        return 1;
    }
    
    static int draw_string(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        
        new_font->drawString(out, x, y);
        float height = new_font->stringHeight(out);
        float width = new_font->stringWidth(out);
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static int draw_string_as_shapes(lua_State *L) {
        ofTrueTypeFont *new_font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        
        new_font->drawStringAsShapes(out, x, y);
        float height = new_font->stringHeight(out);
        float width = new_font->stringWidth(out);
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static const struct luaL_Reg glomp_font[] = {
        {"new", font_new},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg glomp_font_methods [] = {
        {"set_line_height", set_line_height},
        {"set_space_size", set_space_size},
        {"set_letter_spacing", set_letter_spacing},
        {"set_global_dpi", set_global_dpi},
        {"get_string_height", get_string_height},
        {"get_string_width", get_string_width},
        {"get_line_height", get_line_height},
        {"draw", draw_string},
        {"draw_as_shapes", draw_string_as_shapes},
        {"__gc", font_gc},
        {NULL, NULL}
    };
    
    int luaopen_font(lua_State *L) {
        luaL_newmetatable(L, "glomp.font");
        
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        
        luaL_register(L, NULL, glomp_font_methods);
        luaL_register(L, "font", glomp_font);
        
        return 1;
    }

}