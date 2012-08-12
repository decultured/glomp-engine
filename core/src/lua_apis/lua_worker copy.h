//
//  lua_worker.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_worker_h
#define glOMP_lua_worker_h

#include "lua_util.h"
#include "lua_marshal.h"
#include "lua_graphics.h"
#include "lua_font.h"
#include "lua_sound.h"
#include "lua_system.h"
#include "lua_image.h"
#include "lua_window.h"
#include "lua_directory.h"

namespace glOMP {
    
    lua_State *lua_worker_init() {
        lua_State *L = lua_open();
        
        luaL_openlibs(L);
        luaopen_marshal(L);
        
        return L;
    }
    
    void lua_worker_shutdown(lua_State *L) {
        lua_close(L);
    }

    void lua_worker_callback_update(lua_State *L, double frame_time) {
        lua_getglobal(L, "_glOMP_update");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, frame_time);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            lua_report_errors(L, "_glOMP_update");
            return;
        }
    }

}

#endif
