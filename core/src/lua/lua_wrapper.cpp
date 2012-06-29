//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_wrapper.h"
#include "lua_print.h"

namespace glomp {
namespace lua {

LuaWrapper::LuaWrapper() {
    L = NULL;
}

LuaWrapper::~LuaWrapper() {
    shutdown();
}
    
void LuaWrapper::init() {
    shutdown();

    L = lua_open();
    luaL_openlibs(L);
    luaopen_luaprintlib(L);
}

void LuaWrapper::shutdown() {
    if (!L)
        return;
    
    lua_close(L);
    L = NULL;
}
    
void LuaWrapper::load_file(const char *filename) {
    int s = luaL_loadfile(L, filename);
    if ( s==0 ) {
        s = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    report_errors(L, s);
}
    
void LuaWrapper::report_errors(lua_State *L, int status)
{
    if ( status!=0 ) {
        std::cerr << "-- " << lua_tostring(L, -1) << std::endl;

        lua_pop(L, 1);
    }
}

void LuaWrapper::print(const char *message) {
    if (L) lua_print(L, message);
}
    
void LuaWrapper::keyPressed(int key){
    lua_getglobal(L, "_glomp_key_pressed");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, key);
    
    if (lua_pcall(L, 1, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_key_pressed: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::keyReleased(int key){
    lua_getglobal(L, "_glomp_key_released");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, key);
    
    if (lua_pcall(L, 1, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_key_released: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::mouseMoved(int x, int y){
    lua_getglobal(L, "_glomp_mouse_moved");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    
    if (lua_pcall(L, 2, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_mouse_moved: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::mouseDragged(int x, int y, int button){
    lua_getglobal(L, "_glomp_mouse_dragged");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    lua_pushnumber(L, button);
    
    if (lua_pcall(L, 3, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_mouse_dragged: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::mousePressed(int x, int y, int button){
    lua_getglobal(L, "_glomp_mouse_pressed");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    lua_pushnumber(L, button);
    
    if (lua_pcall(L, 3, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_mouse_pressed: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::mouseReleased(int x, int y, int button){
    lua_getglobal(L, "_glomp_mouse_released");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    lua_pushnumber(L, button);
    
    if (lua_pcall(L, 3, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_mouse_released: %s\n" << lua_tostring(L, -1);
        return;
    }
}

void LuaWrapper::windowResized(int w, int h){
    lua_getglobal(L, "_glomp_window_resized");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    lua_pushnumber(L, w);
    lua_pushnumber(L, h);
    
    if (lua_pcall(L, 2, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_window_resized: %s\n" << lua_tostring(L, -1);
        return;
    }
}
    
    
    
}
}