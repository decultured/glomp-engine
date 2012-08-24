//
//  lua_graphics.h
//  glomp
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_lua_gl_h
#define glomp_lua_gl_h

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
    static int lua_graphics_clear(lua_State *L);
    static int lua_graphics_clear_hex(lua_State *L);

    static int lua_graphics_set_color(lua_State *L);
    static int lua_graphics_set_color_hex(lua_State *L);

    static int lua_graphics_push_matrix(lua_State *L);
    static int lua_graphics_pop_matrix(lua_State *L);

    static int lua_graphics_push_2d_transform(lua_State *L);

    static int lua_graphics_rotate(lua_State *L);
    static int lua_graphics_translate(lua_State *L);
    static int lua_graphics_scale(lua_State *L);

    static int lua_graphics_rectangle(lua_State *L);
    static int lua_graphics_circle(lua_State *L);
    static int lua_graphics_ellipse(lua_State *L);
    static int lua_graphics_triangle(lua_State *L);
    static int lua_graphics_line(lua_State *L);
    static int lua_graphics_curve(lua_State *L);

    static int lua_graphics_print(lua_State *L);
    static int lua_graphics_print_highlight(lua_State *L);

    static int lua_graphics_set_line_width(lua_State *L);
    static int lua_graphics_set_circle_resolution(lua_State *L);
    static int lua_graphics_set_curve_resolution(lua_State *L);

    static int lua_graphics_draw_fills(lua_State *L);

    static int lua_graphics_enable_alpha_blending(lua_State *L);
    static int lua_graphics_disable_alpha_blending(lua_State *L);

    static int lua_graphics_enable_smoothing(lua_State *L);
    static int lua_graphics_disable_smoothing(lua_State *L);

    static int lua_graphics_set_viewport(lua_State *L);

    static int lua_graphics_set_ortho(lua_State *L);
    static int lua_graphics_set_perspective(lua_State *L);
    
    void luaopen_graphics(lua_State *L);
}


#endif
