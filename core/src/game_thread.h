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
#include "lua_wrapper.h"
#include "ofEvents.h"

namespace glomp {

class GameThread : public ofThread {
private:
    LuaWrapper lua_wrap;

public:
    void init();

    void threadedFunction();
    
    void shutdown();

    void keyPressed(ofKeyEventArgs &args);
    void keyReleased(ofKeyEventArgs &args);
    
    void mouseMoved(ofMouseEventArgs &args);
    void mouseDragged(ofMouseEventArgs &args);
    void mousePressed(ofMouseEventArgs &args);
    void mouseReleased(ofMouseEventArgs &args);
    void windowResized(ofResizeEventArgs &args);

};

}

#endif
