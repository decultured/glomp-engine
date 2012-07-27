//
//  game_thread.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_game_thread.h"

namespace glomp {

void GameThread::threadedFunction() {
    init();
        
    while(isThreadRunning()) {
//        lua_game.__update();
        this->sleep(10);
    }

    shutdown();
}

void GameThread::init() {
    lua_game.init();

    lua_game.set_lua_path(ofToDataPath("lua/", true).c_str());
    lua_game.load_file(ofToDataPath("lua/game_main.lua").c_str());
}

void GameThread::shutdown() {
    lua_game.shutdown();
}


}