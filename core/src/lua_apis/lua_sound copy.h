//
//  lua_sound.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_sound_h
#define glOMP_lua_sound_h

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
    
    #define glomp_checksound(L, N) *(ofSoundPlayer **)luaL_checkudata(L, N, "glOMP.sound")
    
    static int lua_sound_load(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        bool stream = lua_toboolean(L, 2);
        bool multiplay = lua_toboolean(L, 3);
        
        ofSoundPlayer **sound= (ofSoundPlayer **)lua_newuserdata(L, sizeof(ofSoundPlayer *));
        luaL_getmetatable(L, "glOMP.sound");
        lua_setmetatable(L, -2);
        
        *sound = new ofSoundPlayer();
        
        (*sound)->setMultiPlay(multiplay);
        (*sound)->loadSound(filename, stream);
        
        return 1;
    }
    
    static int lua_sound_gc(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        if (sound->isLoaded())
            sound->unloadSound();
        
        delete sound;
        
        return 0;
    }
    
    static int lua_sound_play(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        sound->play();
        
        return 0;
    }
    
    static int lua_sound_stop(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        sound->stop();
        
        return 0;
    }
    
    static int lua_sound_set_loop(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        bool looping = lua_toboolean(L, 2);
        
        sound->setLoop(looping);
        
        return 0;
    }
    
    static int lua_sound_set_position(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float pos = luaL_checknumber(L, 2);
        
        sound->setPosition(pos);
        
        return 0;
    }
    
    static int lua_sound_get_position(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        lua_pushnumber(L, sound->getPosition());
        
        return 1;
    }
    
    static int lua_sound_set_speed(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float speed = luaL_checknumber(L, 2);
        
        sound->setSpeed(speed);
        
        return 0;
    }
    
    static int lua_sound_set_volume(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float volume = luaL_checknumber(L, 2);
        
        sound->setVolume(volume);
        
        return 0;
    }
    
    static int lua_sound_set_paused(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        bool paused = lua_toboolean(L, 2);
        
        sound->setPaused(paused);
        
        return 0;
    }
    
    static int lua_sound_set_pan(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float pan = luaL_checknumber(L, 2);
        
        sound->setPan(pan);
        
        return 0;
    }
    
    static int lua_sound_is_playing(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        lua_pushboolean(L, sound->getIsPlaying());
        
        return 1;
    }
    
    static const struct luaL_Reg lua_sound_methods[] = {
        {"load", lua_sound_load},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg lua_sound_metamethods [] = {
        {"play", lua_sound_play},
        {"stop", lua_sound_stop},
        {"set_loop", lua_sound_set_loop},
        {"set_position", lua_sound_set_position},
        {"get_position", lua_sound_get_position},
        {"set_speed", lua_sound_set_speed},
        {"set_volume", lua_sound_set_volume},
        {"set_paused", lua_sound_set_paused},
        {"set_pan", lua_sound_set_pan},
        {"is_playing", lua_sound_is_playing},
        {"__gc", lua_sound_gc},
        {NULL, NULL}
    };
    
    void luaopen_sound(lua_State *L) {
        register_metatable(L, "glOMP.sound", lua_sound_metamethods);
        register_module(L, "sound", lua_sound_methods);
    }
    
}

#endif
