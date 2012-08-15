//
//  lua_worker.h
//  glomp
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_lua_worker_h
#define glomp_lua_worker_h

#include "lua_util.h"
#include "lua_marshal.h"
#include "lua_graphics.h"
#include "lua_font.h"
#include "lua_sound.h"
#include "lua_system.h"
#include "lua_image.h"
#include "lua_window.h"
#include "lua_directory.h"

namespace glomp {
    
    lua_State *lua_worker_init();
    
    void lua_worker_shutdown(lua_State *L);

    void lua_worker_callback_update(lua_State *L, double frame_time);
}

#endif
