//
//  game_thread.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/8/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_game_thread_h
#define glOMP_game_thread_h

#include "ofMain.h"
#include "lua_game.h"
#include "ofEvents.h"

#include "Poco/TimedNotificationQueue.h"

namespace glomp {

class WorkerThread : public ofThread {
private:
    LuaWrapper lua_wrap;

    Poco::TimedNotificationQueue& _main_queue;

public:
    WorkerThread(Poco::TimedNotificationQueue& main_queue) : _main_queue(main_queue) {}

    void init();

    void threadedFunction();
    
    void shutdown();
};

}

#endif
