//
//  lua_system.h
//  glOMP
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_system_h
#define glOMP_lua_system_h

#include "lua_util.h"
#include "ofMain.h"

namespace glOMP {
    
    static int lua_system_launch_browser(lua_State *L) {
        const char *url = luaL_checkstring(L, 1);
        
        ofLaunchBrowser(url);
        
        return 0;
    }
    
    static int lua_system_save_screen(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        
        ofSaveScreen(filename);
        
        return 0;
    }
    
    static int lua_system_save_viewport(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        
        ofSaveViewport(filename);
        
        return 0;
    }
    
    static int lua_system_alert(lua_State *L) {
        const char *message = luaL_checkstring(L, 1);
        
        ofSystemAlertDialog(message);
        
        return 0;
    }
    
    static int lua_system_save_dialog(lua_State *L) {
        const char *name = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);
        
        ofFileDialogResult result = ofSystemSaveDialog(name, message);
        
        lua_pushboolean(L, result.bSuccess);
        lua_pushstring(L, result.filePath.c_str());
        lua_pushstring(L, result.fileName.c_str());
        
        return 3;
    }
    
    static int lua_system_load_dialog(lua_State *L) {
        const char *name = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);
        
        ofFileDialogResult result = ofSystemLoadDialog(name, message);
        
        lua_pushboolean(L, result.bSuccess);
        lua_pushstring(L, result.filePath.c_str());
        lua_pushstring(L, result.fileName.c_str());
        
        return 3;
    }
    
    static int lua_system_exit(lua_State *L) {
        int status = lua_isnumber(L, 1) ? lua_tointeger(L, 1) : 0;
        
        ofExit(status);
        
        return 0;
    }
    
    static int lua_system_sleep(lua_State *L) {
        int millis = luaL_checkinteger(L, 1);
        
        ofSleepMillis(millis);
        
        return 0;
    }
    
    static const struct luaL_Reg lua_system_methods[] = {
        {"launch_browser", lua_system_launch_browser},
        {"save_screen", lua_system_save_screen},
        {"save_viewport", lua_system_save_viewport},
        {"alert", lua_system_alert},
        {"save_dialog", lua_system_save_dialog},
        {"load_dialog", lua_system_load_dialog},
        {"exit", lua_system_exit},
        {"sleep", lua_system_sleep},
        {NULL, NULL}
    };
    
    void luaopen_system(lua_State *L) {
        register_module(L, "system", lua_system_methods);
    }

}


#endif
