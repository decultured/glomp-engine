//
//  lua_graphics.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "lua_graphics.h"

namespace glomp {
    
    static int clear(lua_State *L) {
        float r = luaL_checknumber(L, 1);
        float g = luaL_checknumber(L, 2);
        float b = luaL_checknumber(L, 3);

        ofClear(r, g, b);
        
        return 0;
    }
    
    static int push_matrix(lua_State *L) {
        ofPushMatrix();
        return 0;
    }
    
    static int pop_matrix(lua_State *L) {
        ofPopMatrix();
        return 0;
    }
    
    static int rotate(lua_State *L) {
        float amount = luaL_checknumber(L, 1);
        ofRotate(amount);
        return 0;
    }
    
    static int translate(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = lua_isnumber(L, 3) ? luaL_checknumber(L, 3) : 0;

        ofTranslate(x, y, z);
        return 0;
    }
    
    static int scale(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = lua_isnumber(L, 3) ? luaL_checknumber(L, 3) : 1.0f;
            
        ofScale(x, y, z);
        return 0;
    }
    
    static int rect(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
            
        ofRect(x, y, w, h);
        return 0;
    }
    
    static int circle(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float r = luaL_checknumber(L, 3);
        
        ofCircle(x, y, r);
        return 0;
    }
    
    static int line(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        
        ofLine(x, y, x2, y2);
        return 0;
    }
    
    static int draw_filled(lua_State *L) {
        if (lua_toboolean(L, 1)) {
            ofFill();
        } else {
            ofNoFill();
        }
        
        return 0;
    }
    
    static int set_viewport(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
        bool invert_y = lua_toboolean(L, 5);

        ofViewport(x, y, w, h, invert_y);
        
        return 0;
    }

    static const struct luaL_Reg glomp_graphics[] = {
        {"clear", clear},
        {"push_matrix", push_matrix},
        {"pop_matrix", pop_matrix},
        {"rotate", rotate},
        {"translate", translate},
        {"scale", scale},
        {"rect", rect},
        {"circle", circle},
        {"line", line},
        {"draw_filled", draw_filled},
        {NULL, NULL}
    };
    
    int luaopen_graphics(lua_State *L) {
        luaL_register(L, "graphics", glomp_graphics);
        return 1;
    }
}