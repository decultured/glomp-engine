//
//  game_thread.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_worker_thread.h"

namespace glomp {

void WorkerThread::threadedFunction() {
    init();
        
    while(isThreadRunning()) {
        lua_wrap.update(10);
        this->sleep(10);
    }

    shutdown();
}

void WorkerThread::init() {
    lua_wrap.init();

    lua_wrap.set_lua_path(ofToDataPath("lua/", true).c_str());
    lua_wrap.load_file(ofToDataPath("lua/worker_main.lua").c_str());
}

void WorkerThread::shutdown() {
    lua_wrap.shutdown();
}

}
