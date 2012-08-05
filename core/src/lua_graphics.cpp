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
    
    static int set_color(lua_State *L) {
        float r = luaL_checknumber(L, 1);
        float g = luaL_checknumber(L, 2);
        float b = luaL_checknumber(L, 3);
        float a = luaL_checknumber(L, 4);
        
        ofSetColor(r, g, b, a);
        
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
    
    static int ellipse(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
        
        ofEllipse(x, y, w, h);
        return 0;
    }
    
    static int triangle(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        float x3 = luaL_checknumber(L, 5);
        float y3 = luaL_checknumber(L, 6);
    
        ofTriangle(x1, y1, x2, y2, x3, y3);
        
        return 0;
    }
    
    static int line(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        
        ofLine(x1, y1, x2, y2);
        return 0;
    }
    
    static int curve(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        
        float cx1 = luaL_checknumber(L, 1);
        float cy1 = luaL_checknumber(L, 2);
        float cx2 = luaL_checknumber(L, 3);
        float cy2 = luaL_checknumber(L, 4);
        
        ofCurve(cx1, cy1, x1, y1, x2, y2, cx2, cy2);
        
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
    
    static int enable_alpha_blending(lua_State *L) {
        ofEnableAlphaBlending();
        return 0;
    }
    
    static int disable_alpha_blending(lua_State *L) {
        ofDisableAlphaBlending();
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
    
    static int set_ortho(lua_State *L) {
        float w = lua_isnumber(L, 1) ? lua_tonumber(L, 1): ofGetWidth();
        float h = lua_isnumber(L, 2) ? lua_tonumber(L, 2): ofGetHeight();

        float nearDist = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : -1;
        float farDist = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : -1;
        
        ofSetupScreenOrtho(w, h, OF_ORIENTATION_UNKNOWN, true, nearDist, farDist);
        
        return 0;
    }
    
    static int set_perspective(lua_State *L) {
        float w = lua_isnumber(L, 1) ? lua_tonumber(L, 1): ofGetWidth();
        float h = lua_isnumber(L, 2) ? lua_tonumber(L, 2): ofGetHeight();

        float nearDist = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : -1;
        float farDist = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : -1;

        float fov = lua_isnumber(L, 5) ? lua_tonumber(L, 5) : -1;

        ofSetupScreenPerspective(w, h, OF_ORIENTATION_UNKNOWN, true, fov, nearDist, farDist);
        
        return 0;
    }
    
    static const struct luaL_Reg glomp_graphics[] = {
        {"clear", clear},
        {"set_color", set_color},
        {"push_matrix", push_matrix},
        {"pop_matrix", pop_matrix},
        {"rotate", rotate},
        {"translate", translate},
        {"scale", scale},
        {"rect", rect},
        {"circle", circle},
        {"ellipse", ellipse},
        {"line", line},
        {"curve", curve},
        {"enable_alpha_blending", enable_alpha_blending},
        {"disable_alpha_blending", disable_alpha_blending},
        {"draw_filled", draw_filled},
        {"set_viewport", set_viewport},
        {"set_ortho", set_ortho},
        {"set_perspective", set_perspective},
        {NULL, NULL}
    };
    
    int luaopen_graphics(lua_State *L) {
        luaL_register(L, "graphics", glomp_graphics);
        return 1;
    }
}