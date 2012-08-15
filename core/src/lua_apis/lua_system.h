//
//  lua_system.h
//  glomp
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_lua_system_h
#define glomp_lua_system_h

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
    static int lua_system_launch_browser(lua_State *L);

    static int lua_system_save_screen(lua_State *L);
    static int lua_system_save_viewport(lua_State *L);

    static int lua_system_alert(lua_State *L);

    static int lua_system_save_dialog(lua_State *L);
    static int lua_system_load_dialog(lua_State *L);

    static int lua_system_exit(lua_State *L);

    static int lua_system_sleep(lua_State *L);
    
    static int lua_system_callback_loop_test(lua_State *L);

    void luaopen_system(lua_State *L);
}

#endif
