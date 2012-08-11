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
#include "Poco/TimedNotificationQueue.h"

#include "lua_worker.h"

namespace glomp {

class WorkerThread : public ofThread {
private:
    lua_State *L;

    Poco::TimedNotificationQueue& _main_queue;

public:
    WorkerThread(Poco::TimedNotificationQueue& main_queue);
    ~WorkerThread();

    void init();

    void threadedFunction();
    
    void shutdown();
};

}

#endif
