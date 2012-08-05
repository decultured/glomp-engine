//
//  lua_print.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_print.h"
#include "text_view_event.h"

namespace glomp {

static int lua_print_text_event(lua_State *L) {
    static TextViewEvent event;

    event.name = luaL_checkstring(L, 1);
    event.text = luaL_checkstring(L, 2);
    event.x = luaL_checknumber(L, 3);
    event.y = luaL_checknumber(L, 4);
    
    ofNotifyEvent(TextViewEvent::events, event);
    
    return 0;
}

static const struct luaL_reg printlib [] = {
    {"print_more", lua_print_text_event},
    {NULL, NULL}
};

extern int luaopen_luaprintlib(lua_State *L)
{
    lua_getglobal(L, "_G");
    luaL_register(L, NULL, printlib);
    lua_pop(L, 1);
}
    
}