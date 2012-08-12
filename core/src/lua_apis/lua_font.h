//
//  lua_font.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_font_h
#define glOMP_lua_font_h

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
    
    #define glomp_checkfont(L, N) *(ofTrueTypeFont **)luaL_checkudata(L, N, "glOMP.font")
    
    static int lua_font_load(lua_State *L);
    static int lua_font_gc(lua_State *L);

    static int lua_font_set_line_height(lua_State *L);
    static int lua_font_set_letter_spacing(lua_State *L);
    static int lua_font_set_space_size(lua_State *L);
    static int lua_font_set_global_dpi(lua_State *L);
    static int lua_font_get_string_height(lua_State *L);
    static int lua_font_get_string_width(lua_State *L);
    static int lua_font_get_line_height(lua_State *L);
    static int lua_font_draw_string(lua_State *L);
    static int lua_font_draw_string_as_shapes(lua_State *L);
    
    void luaopen_font(lua_State *L);
}

#endif
