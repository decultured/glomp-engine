//
//  lua_window.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/8/12.
//
//

#include "lua_window.h"

namespace glomp {
    
    static int set_fullscreen(lua_State *L) {
        bool fullscreen = lua_toboolean(L, 1);
        
        ofSetFullscreen(fullscreen);
        
        return 0;
    }
    
    static int set_window_title(lua_State *L) {
        const char *title = luaL_checkstring(L, 1);
        
        ofSetWindowTitle(title);
        
        return 0;
    }
    
    static int set_window_shape(lua_State *L) {
        int width = luaL_checkinteger(L, 1);
        int height = luaL_checkinteger(L, 2);
        
        ofSetWindowShape(width, height);
        
        return 0;
    }
    
    static int get_window_shape(lua_State *L) {
        int width = ofGetWindowWidth();
        int height = ofGetWindowHeight();
        
        lua_pushnumber(L, width);
        lua_pushnumber(L, height);
        
        return 2;
    }
    
    static int set_window_position(lua_State *L) {
        int x = luaL_checkinteger(L, 1);
        int y = luaL_checkinteger(L, 2);
        
        ofSetWindowPosition(x, y);
        
        return 0;
    }
    
    static int get_window_position(lua_State *L) {
        int x = ofGetWindowPositionX();
        int y = ofGetWindowPositionY();
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        
        return 2;
    }
    
    static int get_screen_size(lua_State *L) {
        int height = ofGetScreenWidth();
        int width = ofGetScreenHeight();
        
        lua_pushnumber(L, 1);
        lua_pushnumber(L, 2);

        return 2;
    }
    
    static int hide_cursor(lua_State *L) {
        ofHideCursor();
        
        return 0;
    }
    
    static int show_cursor(lua_State *L) {
        ofShowCursor();
        
        return 0;
    }
    
    static int set_vsync(lua_State *L) {
        bool vsync = lua_toboolean(L, 1);
        
        ofSetVerticalSync(vsync);
        
        return 0;
    }
    
    static int show_setup_screen(lua_State *L) {
        ofEnableSetupScreen();

        return 0;
    }
    
    static int hide_setup_screen(lua_State *L) {
        ofDisableSetupScreen();
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_window[] = {
        {"set_fullscreen", set_fullscreen},
        {"set_title", set_window_title},
        {"set_size", set_window_shape},
        {"get_size", get_window_shape},
        {"set_position", set_window_position},
        {"get_position", get_window_position},
        {"get_screen_size", get_screen_size},
        {"hide_cursor", hide_cursor},
        {"show_cursor", show_cursor},
        {"set_vsync", set_vsync},
        {"show_setup_screen", show_setup_screen},
        {"hide_setup_screen", hide_setup_screen},
        {NULL, NULL}
    };
    
    int luaopen_window(lua_State *L) {
        luaL_register(L, "window", glomp_window);
        return 1;
    }
}