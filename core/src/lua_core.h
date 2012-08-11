//
//  lua_core.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_core_h
#define glOMP_lua_core_h

#include "lua_util.h"
#include "lua_marshal.h"
#include "lua_graphics.h"
#include "lua_font.h"
#include "lua_sound.h"
#include "lua_system.h"
#include "lua_image.h"
#include "lua_window.h"
#include "lua_directory.h"

namespace glOMP {
    
    lua_State *lua_core_init() {
        lua_State *L = lua_open();

        luaL_openlibs(L);

        luaopen_marshal(L);
        luaopen_app(L);
        luaopen_graphics(L);
        luaopen_font(L);
        luaopen_sound(L);
        luaopen_glomp_system(L);
        luaopen_image(L);
        luaopen_window(L);
        luaopen_directory(L);
    }
    
    void lua_core_shutdown(lua_State *L) {
        lua_close(L);
    }
    
    void lua_core_callback_key_pressed(lua_State *L, int key){
        lua_getglobal(L, "_glomp_key_pressed");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, key);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_key_pressed");
            return;
        }
    }
    
    void lua_core_callback_key_released(lua_State *L, int key){
        lua_getglobal(L, "_glomp_key_released");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, key);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_key_released");
            return;
        }
    }
    
    void lua_core_callback_mouse_moved(lua_State *L, int x, int y){
        lua_getglobal(L, "_glomp_mouse_moved");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        
        if (lua_pcall(L, 2, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_mouse_moved");
            return;
        }
    }
    
    void lua_core_callback_mouse_dragged(lua_State *L, int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_dragged");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_mouse_dragged");
            return;
        }
    }
    
    void lua_core_callback_mouse_pressed(lua_State *L, int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_pressed");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_mouse_pressed");
            return;
        }
    }
    
    void lua_core_callback_mouse_released(lua_State *L, int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_released");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_mouse_released");
            return;
        }
    }
    
    void lua_core_callback_window_resized(lua_State *L, int w, int h){
        lua_getglobal(L, "_glomp_window_resized");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, w);
        lua_pushnumber(L, h);
        
        if (lua_pcall(L, 2, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_window_resized");
            return;
        }
    }
    
    void lua_core_callback_update(lua_State *L, double frame_time) {
        lua_getglobal(L, "_glomp_update");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, frame_time);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            report_errors(L, "_glomp_update");
            return;
        }
    }

    void lua_core_callback_draw(lua_State *L) {
        lua_getglobal(L, "_glomp_draw");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        if (lua_pcall(L, 0, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_draw");
            return;
        }
    }
    
    void lua_core_callback_window_entry(lua_State *L, int state) {
        lua_getglobal(L, "_glomp_window_entry");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, state);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            lua_report_errors(L, "_glomp_window_entry");
            return;
        }
    }
    
}

#endif
