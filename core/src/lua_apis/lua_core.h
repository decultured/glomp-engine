//
//  lua_core.h
//  glomp
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_lua_core_h
#define glomp_lua_core_h

#include "lua_util.h"
#include "lua_marshal.h"
#include "lua_graphics.h"
#include "lua_font.h"
#include "lua_sound.h"
#include "lua_system.h"
#include "lua_image.h"
#include "lua_window.h"
#include "lua_directory.h"
#include "lua_matrix4x4.h"

namespace glomp {
    
    lua_State *lua_core_init();
    void lua_core_shutdown(lua_State *L);

    void lua_core_callback_key_pressed(lua_State *L, int key);
    void lua_core_callback_key_released(lua_State *L, int key);

    void lua_core_callback_mouse_moved(lua_State *L, int x, int y);
    void lua_core_callback_mouse_dragged(lua_State *L, int x, int y, int button);
    void lua_core_callback_mouse_pressed(lua_State *L, int x, int y, int button);
    void lua_core_callback_mouse_released(lua_State *L, int x, int y, int button);

    void lua_core_callback_window_resized(lua_State *L, int w, int h);
    void lua_core_callback_window_entry(lua_State *L, int state);

    void lua_core_callback_update(lua_State *L, double frame_time);
    void lua_core_callback_draw(lua_State *L);

    void lua_core_callback_got_message(lua_State *L, ofMessage msg);
    void lua_core_callback_drag_event(lua_State *L, ofDragInfo dragInfo);
}

#endif
