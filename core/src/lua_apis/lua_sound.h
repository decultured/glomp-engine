//
//  lua_sound.h
//  glomp
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_lua_sound_h
#define glomp_lua_sound_h

#include "lua_util.h"
#include "ofMain.h"

namespace glomp {
    
    #define glomp_checksound(L, N) *(ofSoundPlayer **)luaL_checkudata(L, N, "glomp.sound")
    
    static int lua_sound_load(lua_State *L);
    static int lua_sound_gc(lua_State *L);
    
    static int lua_sound_play(lua_State *L);
    static int lua_sound_set_paused(lua_State *L);
    static int lua_sound_stop(lua_State *L);
    
    static int lua_sound_set_loop(lua_State *L);
    static int lua_sound_set_position(lua_State *L);
    static int lua_sound_get_position(lua_State *L);
    static int lua_sound_set_speed(lua_State *L);
    static int lua_sound_set_volume(lua_State *L);
    static int lua_sound_set_pan(lua_State *L);
    static int lua_sound_is_playing(lua_State *L);
    
    void luaopen_sound(lua_State *L);
}

#endif
