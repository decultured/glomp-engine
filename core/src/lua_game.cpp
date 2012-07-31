//
//  lua_game.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_game.h"

namespace glomp {

LuaGame::LuaGame() : LuaWrapper() {
}

LuaGame::~LuaGame() {
    shutdown();
}

void LuaGame::init() {
    LuaWrapper::init();
}

void LuaGame::shutdown() {
    LuaWrapper::shutdown();
}

void LuaGame::update() {
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
