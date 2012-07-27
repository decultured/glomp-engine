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

}
