//
//  lua_system.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_system.h"

namespace glomp {
    
    static int launch_browser(lua_State *L) {
        const char *url = luaL_checkstring(L, 1);
        
        ofLaunchBrowser(url);
        
        return 0;
    }
    
    static int save_screen(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        
        ofSaveScreen(filename);
        
        return 0;
    }
    
    static int save_viewport(lua_State *L) {
        const char *filename = luaL_checkstring(L, 1);
        
        ofSaveViewport(filename);
        
        return 0;
    }
    
    static int system_alert(lua_State *L) {
        const char *message = luaL_checkstring(L, 1);
        
        ofSystemAlertDialog(message);
        
        return 0;
    }

    static int system_save_dialog(lua_State *L) {
        const char *name = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);
        
        ofFileDialogResult result = ofSystemSaveDialog(name, message);
        
        lua_pushboolean(L, result.bSuccess);
        lua_pushstring(L, result.filePath.c_str());
        lua_pushstring(L, result.fileName.c_str());
        
        return 3;
    }
    
    static int system_load_dialog(lua_State *L) {
        const char *name = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);
        
        ofFileDialogResult result = ofSystemLoadDialog(name, message);
        
        lua_pushboolean(L, result.bSuccess);
        lua_pushstring(L, result.filePath.c_str());
        lua_pushstring(L, result.fileName.c_str());
        
        return 3;
    }
    
    static int app_exit(lua_State *L) {
        int status = lua_isnumber(L, 1) ? lua_tointeger(L, 1) : 0;
        
        ofExit(status);
        
        return 0;
    }
    
    static int app_sleep_millis(lua_State *L) {
        int millis = luaL_checkinteger(L, 1);
        
        ofSleepMillis(millis);
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_system[] = {
        {"launch_browser", launch_browser},
        {"save_screen", save_screen},
        {"save_viewport", save_viewport},
        {"alert", system_alert},
        {"save_dialog", system_save_dialog},
        {"load_dialog", system_load_dialog},
        {"exit", app_exit},
        {"sleep", app_sleep_millis},
        {NULL, NULL}
    };
    
    int luaopen_glomp_system(lua_State *L) {
        luaL_register(L, "system", glomp_system);
        return 1;
    }
}