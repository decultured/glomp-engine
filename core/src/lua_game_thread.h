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

namespace glomp {

class GameThread : public ofThread {
private:
    LuaGame lua_game;

public:
    void init();

    void threadedFunction();
    
    void shutdown();
};

}

#endif
