//
//  lua_sound.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <string>
#include "lua_sound.h"

namespace glomp {
    
#define glomp_checksound(L, N) *(ofSoundPlayer **)luaL_checkudata(L, N, "glomp.sound")
    
    static int sound_new(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        bool stream = lua_toboolean(L, 2);
        bool multiplay = lua_toboolean(L, 3);
        
        ofSoundPlayer **sound= (ofSoundPlayer **)lua_newuserdata(L, sizeof(ofSoundPlayer *));
        luaL_getmetatable(L, "glomp.sound");
        lua_setmetatable(L, -2);
        
        *sound = new ofSoundPlayer();
        
        (*sound)->setMultiPlay(multiplay);
        (*sound)->loadSound(filename, stream);

        return 1;
    }
    
    static int sound_gc(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        if (sound->isLoaded())
            sound->unloadSound();
        
        delete sound;
        
        return 0;
    }
    
    static int play_sound(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        sound->play();
        
        return 0;
    }
    
    static int stop_sound(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        sound->stop();
        
        return 0;
    }
    
    static int set_loop(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        bool looping = lua_toboolean(L, 1);
        
        sound->setLoop(looping);
        
        return 0;
    }
    
    static int set_position(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float pos = luaL_checknumber(L, 1);
        
        sound->setPosition(pos);
        
        return 0;
    }
    
    static int set_speed(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float speed = luaL_checknumber(L, 1);
        
        sound->setSpeed(speed);
        
        return 0;
    }

    static int set_volume(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float volume = luaL_checknumber(L, 1);
        
        sound->setVolume(volume);
        
        return 0;
    }
    
    static int set_paused(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        bool paused = lua_toboolean(L, 1);
        
        sound->setPaused(paused);
        
        return 0;
    }
    
    static int set_pan(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        float pan = luaL_checknumber(L, 1);
        
        sound->setPan(pan);
        
        return 0;
    }
    
    static int get_is_playing(lua_State *L) {
        ofSoundPlayer *sound= glomp_checksound(L, 1);
        
        lua_pushboolean(L, sound->getIsPlaying());
        
        return 1;
    }
   
    static const struct luaL_Reg glomp_sound[] = {
        {"new", sound_new},
        {NULL, NULL}
    };
    
    
    static const struct luaL_Reg glomp_sound_methods [] = {
        {"play", play_sound},
        {"stop", stop_sound},
        {"set_loop", set_loop},
        {"set_position", set_position},
        {"set_speed", set_speed},
        {"set_volume", set_volume},
        {"set_paused", set_paused},
        {"set_pan", set_pan},
        {"is_playing", get_is_playing},
        {"__gc", sound_gc},
        {NULL, NULL}
    };
    
    int luaopen_sound(lua_State *L) {
        luaL_newmetatable(L, "glomp.sound");
        
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        
        luaL_register(L, NULL, glomp_sound_methods);
        luaL_register(L, "sound", glomp_sound);
        
        return 1;
    }
}