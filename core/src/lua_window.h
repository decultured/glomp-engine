//
//  lua_window.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#ifndef __glOMP__lua_window__
#define __glOMP__lua_window__

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
    
    static int lua_window_set_fullscreen(lua_State *L) {
        bool fullscreen = lua_toboolean(L, 1);
        
        ofSetFullscreen(fullscreen);
        
        return 0;
    }
    
    static int lua_window_set_title(lua_State *L) {
        const char *title = luaL_checkstring(L, 1);
        
        ofSetWindowTitle(title);
        
        return 0;
    }
    
    static int lua_window_set_size(lua_State *L) {
        int width = luaL_checkinteger(L, 1);
        int height = luaL_checkinteger(L, 2);
        
        ofSetWindowShape(width, height);
        
        return 0;
    }
    
    static int lua_window_get_size(lua_State *L) {
        int width = ofGetWindowWidth();
        int height = ofGetWindowHeight();
        
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static int lua_window_set_position(lua_State *L) {
        int x = luaL_checkinteger(L, 1);
        int y = luaL_checkinteger(L, 2);
        
        ofSetWindowPosition(x, y);
        
        return 0;
    }
    
    static int lua_window_get_position(lua_State *L) {
        int x = ofGetWindowPositionX();
        int y = ofGetWindowPositionY();
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        
        return 2;
    }
    
    static int lua_window_get_screen_size(lua_State *L) {
        int height = ofGetScreenWidth();
        int width = ofGetScreenHeight();
        
        lua_pushnumber(L, 1);
        lua_pushnumber(L, 2);
        
        return 2;
    }
    
    static int lua_window_hide_cursor(lua_State *L) {
        ofHideCursor();
        
        return 0;
    }
    
    static int lua_window_show_cursor(lua_State *L) {
        ofShowCursor();
        
        return 0;
    }
    
    static int lua_window_set_vsync(lua_State *L) {
        bool vsync = lua_toboolean(L, 1);
        
        ofSetVerticalSync(vsync);
        
        return 0;
    }
    
    static int lua_window_show_setup_screen(lua_State *L) {
        ofEnableSetupScreen();
        
        return 0;
    }
    
    static int lua_window_hide_setup_screen(lua_State *L) {
        ofDisableSetupScreen();
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_window[] = {
        {"set_fullscreen", lua_window_set_fullscreen},
        {"set_title", lua_window_set_title},
        {"set_size", lua_window_set_size},
        {"get_size", lua_window_get_size},
        {"set_position", lua_window_set_position},
        {"get_position", lua_window_get_position},
        {"get_screen_size", lua_window_get_screen_size},
        {"hide_cursor", lua_window_hide_cursor},
        {"show_cursor", lua_window_show_cursor},
        {"set_vsync", lua_window_set_vsync},
        {"show_setup_screen", lua_window_show_setup_screen},
        {"hide_setup_screen", lua_window_hide_setup_screen},
        {NULL, NULL}
    };
    
    void luaopen_window(lua_State *L) {
        register_module(L, "window", glomp_window);
    }
}

#endif
