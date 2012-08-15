//
//  lua_window.h
//  glomp
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#ifndef __glomp__lua_window__
#define __glomp__lua_window__

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
    static int lua_window_set_fullscreen(lua_State *L);
    
    static int lua_window_set_title(lua_State *L);
    
    static int lua_window_set_size(lua_State *L);
    static int lua_window_get_size(lua_State *L);
    
    static int lua_window_set_position(lua_State *L);
    static int lua_window_get_position(lua_State *L);
    
    static int lua_window_get_screen_size(lua_State *L);
    
    static int lua_window_hide_cursor(lua_State *L);
    static int lua_window_show_cursor(lua_State *L);
    
    static int lua_window_set_vsync(lua_State *L);
    
    static int lua_window_show_setup_screen(lua_State *L);
    static int lua_window_hide_setup_screen(lua_State *L);
    
    void luaopen_window(lua_State *L);
}

#endif
