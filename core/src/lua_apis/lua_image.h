//
//  lua_image.h
//  glomp
//
//  Created by Jeffrey Graves on 8/7/12.
//
//

#ifndef glomp_lua_image_h
#define glomp_lua_image_h

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
    #define glomp_checkimage(L, N) *(ofImage **)luaL_checkudata(L, N, "glomp.image")
    
    static int lua_image_load(lua_State *L);
    static int lua_image_load_from_screen(lua_State *L);
    static int lua_image_gc(lua_State *L);
    
    static int lua_image_draw(lua_State *L);
    static int lua_image_draw_subsection(lua_State *L);
    
    static int lua_image_get_width(lua_State *L);
    static int lua_image_get_height(lua_State *L);
    
    static int lua_image_get_color_at(lua_State *L);
    
    static int lua_image_mirror(lua_State *L);
    static int lua_image_resize(lua_State *L);
    static int lua_image_crop(lua_State *L);
    
    void luaopen_image(lua_State *L);
}

#endif
