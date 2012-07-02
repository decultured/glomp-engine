//
//  lua_wrapper.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_wrapper_h
#define glOMP_lua_wrapper_h

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace glomp {
namespace lua {

class LuaWrapper {
private:
    lua_State *L;
    
public:
    LuaWrapper();
    ~LuaWrapper();
    
    void init();
    void shutdown();
    
    int set_lua_path(const char* path);

    void print(const char *message);
    void report_errors(lua_State *L, int status);
    bool load_file(const char *filename);
    void error (lua_State *L, const char *fmt, ...);

    void terminate_app();
    void __update();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
};
    
}
}
        
#endif
