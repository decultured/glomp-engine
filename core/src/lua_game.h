//
//  lua_game.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_game_h
#define glOMP_lua_game_h

#include "lua_wrapper.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace glomp {
    
    class LuaGame : public LuaWrapper {
    public:
        LuaGame();
        ~LuaGame();
        
        void init();
        void shutdown();
    };
    
}



#endif
