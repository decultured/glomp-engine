//
//  lua_wrapper.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_wrapper_h
#define glOMP_lua_wrapper_h

#include <iostream>
#include <sstream>
#include <string>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace glomp {

class LuaWrapper {
protected:
    lua_State *L;
    
public:
    LuaWrapper();
    ~LuaWrapper();
    
    void init();
    void shutdown();
    
    int set_lua_path(const char* path);

    void print(const char *message);
    void print(std::string &message);
    void report_errors(lua_State *L, const char *message);
    bool load_file(const char *filename);
    
    void update(double frame_time);
};
    
}
        
#endif
