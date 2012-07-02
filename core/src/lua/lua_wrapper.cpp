//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include <string>
#include "lua_wrapper.h"
#include "lua_print.h"
#include "lua_graphic.h"

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
    glomp::graphics::luaopen_graphic(L);
}

void LuaWrapper::shutdown() {
    if (!L)
        return;
    
    lua_close(L);
    L = NULL;
}
    
int LuaWrapper::set_lua_path(const char* path)  
{
    std::string new_path;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
    new_path = lua_tostring( L, -1 ); // grab path string from top of stack
    new_path = new_path + ";"; // do your path magic here
    new_path = new_path + path;
    new_path = new_path + "?.lua";
    lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( L, new_path.c_str()); // push the new one
    lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( L, 1 ); // get rid of package table from top of stack
    lua_pushstring(L, path);
    lua_setglobal(L, "LUA_PATH");
    return 0; // all done!
}

void LuaWrapper::error (lua_State *L, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
//    lua_close(L);
//    this->L = NULL;
//    exit(EXIT_FAILURE);
}


bool LuaWrapper::load_file(const char *filename) {
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0)) {
        std::cout << "### cannot run config. file:" << std::endl 
                    << "###     " << lua_tostring(L, -1);
        lua_pop(L, 1);
        
        return false;
    }
    return true;
}

    
void LuaWrapper::report_errors(lua_State *L, int status)
{
    std::cout << "Errors Found: " << status;
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
    
void LuaWrapper::__update() {
    lua_getglobal(L, "_glomp_update");
    if(!lua_isfunction(L,-1)) {
        lua_pop(L,1);
        return;
    }
    
    if (lua_pcall(L, 0, 0, 0) != 0) {
        std::cout << "error calling lua _glomp_update: %s\n" << lua_tostring(L, -1);
        return;
    }
}
    
}
}