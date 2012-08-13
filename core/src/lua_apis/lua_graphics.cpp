//
//  lua_graphics.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 8/4/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "lua_graphics.h"

namespace glOMP {
    
    static int lua_graphics_clear(lua_State *L) {
        float r = luaL_checknumber(L, 1);
        float g = luaL_checknumber(L, 2);
        float b = luaL_checknumber(L, 3);
        
        ofClear(r, g, b);
        
        return 0;
    }
    
    static int lua_graphics_set_color(lua_State *L) {
        float r = luaL_checknumber(L, 1);
        float g = luaL_checknumber(L, 2);
        float b = luaL_checknumber(L, 3);
        float a = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : 255;
        
        ofSetColor(r, g, b, a);
        
        return 0;
    }
    
    static int lua_graphics_push_matrix(lua_State *L) {
        ofPushMatrix();
        return 0;
    }
    
    static int lua_graphics_pop_matrix(lua_State *L) {
        ofPopMatrix();
        return 0;
    }
    
    static int lua_graphics_push_2d_transform(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float rot = luaL_checknumber(L, 3);
        float sx = luaL_checknumber(L, 4);
        float sy = luaL_checknumber(L, 5);
        
        ofPushMatrix();
        ofTranslate(x, y, 0);
        ofRotate(rot);
        ofScale(sx, sy, 1.0f);
        
        return 0;
    }
    
    static int lua_graphics_rotate(lua_State *L) {
        float amount = luaL_checknumber(L, 1);
        ofRotate(amount);
        return 0;
    }
    
    static int lua_graphics_translate(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = lua_isnumber(L, 3) ? luaL_checknumber(L, 3) : 0;
        
        ofTranslate(x, y, z);
        return 0;
    }
    
    static int lua_graphics_scale(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = lua_isnumber(L, 3) ? luaL_checknumber(L, 3) : 1.0f;
        
        ofScale(x, y, z);
        return 0;
    }
    
    static int lua_graphics_rectangle(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
        
        ofRect(x, y, w, h);
        return 0;
    }
    
    static int lua_graphics_circle(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float r = luaL_checknumber(L, 3);
        
        ofCircle(x, y, r);
        return 0;
    }
    
    static int lua_graphics_ellipse(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
        
        ofEllipse(x, y, w, h);
        return 0;
    }
    
    static int lua_graphics_triangle(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        float x3 = luaL_checknumber(L, 5);
        float y3 = luaL_checknumber(L, 6);
        
        ofTriangle(x1, y1, x2, y2, x3, y3);
        
        return 0;
    }
    
    static int lua_graphics_line(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        
        ofLine(x1, y1, x2, y2);
        return 0;
    }
    
    static int lua_graphics_curve(lua_State *L) {
        float x1 = luaL_checknumber(L, 1);
        float y1 = luaL_checknumber(L, 2);
        float x2 = luaL_checknumber(L, 3);
        float y2 = luaL_checknumber(L, 4);
        
        float cx1 = luaL_checknumber(L, 5);
        float cy1 = luaL_checknumber(L, 6);
        float cx2 = luaL_checknumber(L, 7);
        float cy2 = luaL_checknumber(L, 8);
        
        ofCurve(cx1, cy1, x1, y1, x2, y2, cx2, cy2);
        
        return 0;
    }
    
    static int lua_graphics_print(lua_State *L) {
        const char *text = luaL_checkstring(L, 1);
        float x = lua_isnumber(L, 2) ? lua_tonumber(L, 2) : 0;
        float y = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 0;
        
        ofDrawBitmapString(text, x, y);
        
        return 0;
    }
    
    static int lua_graphics_print_highlight(lua_State *L) {
        const char *text = luaL_checkstring(L, 1);
        float x = lua_isnumber(L, 2) ? lua_tonumber(L, 2) : 0;
        float y = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : 0;
        
        ofDrawBitmapStringHighlight(text, x, y);
        
        return 0;
    }
    
    static int lua_graphics_set_line_width(lua_State *L) {
        float w = luaL_checknumber(L, 1);
        
        ofSetLineWidth(w);
        
        return 0;
    }
    
    static int lua_graphics_set_circle_resolution(lua_State *L) {
        int res = luaL_checknumber(L, 1);
        
        ofSetCircleResolution(res);
        
        return 0;
    }
    
    static int lua_graphics_set_curve_resolution(lua_State *L) {
        int res = luaL_checknumber(L, 1);
        
        ofSetCurveResolution(res);
        
        return 0;
    }
    
    static int lua_graphics_draw_fills(lua_State *L) {
        if (lua_toboolean(L, 1)) {
            ofFill();
        } else {
            ofNoFill();
        }
        
        return 0;
    }
    
    static int lua_graphics_enable_alpha_blending(lua_State *L) {
        ofEnableAlphaBlending();
        return 0;
    }
    
    static int lua_graphics_disable_alpha_blending(lua_State *L) {
        ofDisableAlphaBlending();
        return 0;
    }
    
    static int lua_graphics_enable_smoothing(lua_State *L) {
        ofEnableSmoothing();
        return 0;
    }
    
    static int lua_graphics_disable_smoothing(lua_State *L) {
        ofDisableSmoothing();
        return 0;
    }
    
    static int lua_graphics_set_viewport(lua_State *L) {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);
        bool invert_y = lua_toboolean(L, 5);
        
        ofViewport(x, y, w, h, invert_y);
        
        return 0;
    }
    
    static int lua_graphics_set_ortho(lua_State *L) {
        float w = lua_isnumber(L, 1) ? lua_tonumber(L, 1): ofGetWidth();
        float h = lua_isnumber(L, 2) ? lua_tonumber(L, 2): ofGetHeight();
        
        float nearDist = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : -1;
        float farDist = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : -1;
        
        ofSetupScreenOrtho(w, h, OF_ORIENTATION_UNKNOWN, true, nearDist, farDist);
        
        return 0;
    }
    
    static int lua_graphics_set_perspective(lua_State *L) {
        float w = lua_isnumber(L, 1) ? lua_tonumber(L, 1): ofGetWidth();
        float h = lua_isnumber(L, 2) ? lua_tonumber(L, 2): ofGetHeight();
        
        float nearDist = lua_isnumber(L, 3) ? lua_tonumber(L, 3) : -1;
        float farDist = lua_isnumber(L, 4) ? lua_tonumber(L, 4) : -1;
        
        float fov = lua_isnumber(L, 5) ? lua_tonumber(L, 5) : -1;
        
        ofSetupScreenPerspective(w, h, OF_ORIENTATION_UNKNOWN, true, fov, nearDist, farDist);
        
        return 0;
    }
    
    static const struct luaL_Reg lua_graphics_methods[] = {
        {"clear", lua_graphics_clear},
        {"set_color", lua_graphics_set_color},
        {"push_matrix", lua_graphics_push_matrix},
        {"pop_matrix", lua_graphics_pop_matrix},
        {"push_2d_transform", lua_graphics_push_2d_transform},
        {"rotate", lua_graphics_rotate},
        {"translate", lua_graphics_translate},
        {"scale", lua_graphics_scale},
        {"rectangle", lua_graphics_rectangle},
        {"circle", lua_graphics_circle},
        {"ellipse", lua_graphics_ellipse},
        {"line", lua_graphics_line},
        {"curve", lua_graphics_curve},
        {"print", lua_graphics_print},
        {"print_highlight", lua_graphics_print_highlight},
        {"set_curve_resolution", lua_graphics_set_curve_resolution},
        {"set_circle_resolution", lua_graphics_set_circle_resolution},
        {"enable_alpha_blending", lua_graphics_enable_alpha_blending},
        {"disable_alpha_blending", lua_graphics_disable_alpha_blending},
        {"enable_smoothing", lua_graphics_enable_smoothing},
        {"disable_smoothing", lua_graphics_disable_smoothing},
        {"set_line_width", lua_graphics_set_line_width},
        {"draw_fills", lua_graphics_draw_fills},
        {"set_viewport", lua_graphics_set_viewport},
        {"set_ortho", lua_graphics_set_ortho},
        {"set_perspective", lua_graphics_set_perspective},
        {NULL, NULL}
    };
    
    void luaopen_graphics(lua_State *L) {
        register_module(L, "graphics", lua_graphics_methods);
    }
}
