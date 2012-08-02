//
//  lua_app.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_app_h
#define glOMP_lua_app_h

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace glomp {
    
    class LuaApp : public LuaWrapper {
    public:
        LuaApp();
        ~LuaApp();
        
        void init();
        void shutdown();
        
        void terminate_app();
        void update(double frame_time);
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void windowEntry(int state);
    };
    
}

#endif
