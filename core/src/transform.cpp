//
//  transform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include "transform.h"
#include "ofMain.h"

namespace glomp {
    
Transform::Transform() {

}

Transform::~Transform() {

}

void Transform::push() {
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(rotation);
    ofScale(scale_x, scale_y);
}

void Transform::pop() {
    ofPopMatrix();
}

}