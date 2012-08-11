//
//  game_thread.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "worker_thread.h"

namespace glomp {

WorkerThread::WorkerThread(Poco::TimedNotificationQueue& main_queue)
                :_main_queue(main_queue) {
    L = NULL;
}

WorkerThread::~WorkerThread() {
    shutdown();
}

void WorkerThread::threadedFunction() {
    init();
        
    while(isThreadRunning()) {
        glOMP::lua_worker_callback_update(L, 10);
        this->sleep(10);
    }

    shutdown();
}

void WorkerThread::init() {
    if (L) {
        glOMP::lua_worker_shutdown(L);
    }
    L = glOMP::lua_worker_init();
    glOMP::lua_set_path(L, ofToDataPath("lua/", true).c_str());
    glOMP::lua_load_file(L, ofToDataPath("lua/worker_main.lua").c_str());
}

void WorkerThread::shutdown() {
    if (L) {
        glOMP::lua_worker_shutdown(L);
        L = NULL;
    }
}

}
