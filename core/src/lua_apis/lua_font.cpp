//
//  lua_font.cpp
//  glomp
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "lua_font.h"

namespace glomp {
    
    static int lua_font_load(lua_State *L) {
        std::string filename = luaL_checkstring(L, 1);
        int fontsize = luaL_checkint(L, 2);
        bool antialiased = lua_toboolean(L, 3);
        bool full_char_set = lua_toboolean(L, 4);
        bool make_contours = lua_toboolean(L, 5);
        float simplify_amount = lua_isnumber(L, 6) ? luaL_checknumber(L, 6) : 0.3;
        int dpi = lua_isnumber(L, 7) ? luaL_checkint(L, 7) : 0;
        
        ofTrueTypeFont **font= (ofTrueTypeFont **)lua_newuserdata(L, sizeof(ofTrueTypeFont *));
        luaL_getmetatable(L, "glomp.font");
        lua_setmetatable(L, -2);
        
        *font= new ofTrueTypeFont();
        
        (*font)->loadFont(filename.c_str(), fontsize,
                          antialiased, full_char_set,
                          make_contours, simplify_amount, dpi);
        
        return 1;
    }
    
    static int lua_font_gc(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        delete font;
        
        return 0;
    }
    
    static int lua_font_set_line_height(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        float line_height = luaL_checknumber(L, 2);
        
        font->setLineHeight(line_height);
        
        return 0;
    }
    
    static int lua_font_set_letter_spacing(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        float letter_spacing = luaL_checknumber(L, 2);
        
        font->setLetterSpacing(letter_spacing);
        
        return 0;
    }
    
    static int lua_font_set_space_size(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        float space_size = luaL_checknumber(L, 2);
        
        font->setSpaceSize(space_size);
        
        return 0;
    }
    
    static int lua_font_set_global_dpi(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        int dpi = luaL_checkint(L, 1);
        
        font->setGlobalDpi(dpi);
        
        return 0;
    }
    
    static int lua_font_get_string_height(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 2);
        
        float height = font->stringHeight(out);
        lua_pushnumber(L, height);
        
        return 1;
    }
    
    static int lua_font_get_string_width(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 2);
        
        float width = font->stringWidth(out);
        lua_pushnumber(L, width);
        
        return 1;
    }
    
    static int lua_font_get_line_height(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        float height = font->getLineHeight();
        lua_pushnumber(L, height);
        
        return 1;
    }
    
    static int lua_font_draw_string(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 2);
        float x = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 0;
        float y = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0;
        
        font->drawString(out, x, y);
        float height = font->stringHeight(out);
        float width = font->stringWidth(out);
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static int lua_font_draw_string_as_shapes(lua_State *L) {
        ofTrueTypeFont *font= glomp_checkfont(L, 1);
        
        const char * out = luaL_checkstring(L, 2);
        float x = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 0;
        float y = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 0;
        
        font->drawStringAsShapes(out, x, y);
        float height = font->stringHeight(out);
        float width = font->stringWidth(out);
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static const struct luaL_Reg lua_font_methods[] = {
        {"load", lua_font_load},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg lua_font_metamethods [] = {
        {"set_line_height", lua_font_set_line_height},
        {"set_space_size", lua_font_set_space_size},
        {"set_letter_spacing", lua_font_set_letter_spacing},
        {"set_global_dpi", lua_font_set_global_dpi},
        {"get_string_height", lua_font_get_string_height},
        {"get_string_width", lua_font_get_string_width},
        {"get_line_height", lua_font_get_line_height},
        {"draw_string", lua_font_draw_string},
        {"draw_string_as_shapes", lua_font_draw_string_as_shapes},
        {"__gc", lua_font_gc},
        {NULL, NULL}
    };
    
    void luaopen_font(lua_State *L) {
        register_metatable(L, "glomp.font", lua_font_metamethods);
        register_module(L, "font", lua_font_methods);
    }
}
