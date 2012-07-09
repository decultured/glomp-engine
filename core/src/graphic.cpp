//
//  graphic.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/28/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "graphic.h"
#include "ofMain.h"

namespace glomp {

Graphic::Graphic() {
    _parent = NULL;
    _x = 0;
    _y = 0;
    _rot = 0;
    _x_scale = 1.0f;
    _y_scale = 1.0f;
}

Graphic::~Graphic() {
    
}

Graphic *Graphic::add_child(Graphic *new_child) {
    _children.push_back(new_child);
}

void Graphic::Render() {
    PreDraw();
    Draw();
    PostDraw();
}

void Graphic::PreDraw() {
    ofPushMatrix();
    ofTranslate(_x, _y);
    ofRotate(_rot);
    ofScale(_x_scale, _y_scale);
}

void Graphic::Draw() {

}

void Graphic::PostDraw() {
    for (_draw_iter = _children.begin(); _draw_iter != _children.end(); ++_draw_iter) {
        (*_draw_iter)->Render();
    }
    ofPopMatrix();
}

}