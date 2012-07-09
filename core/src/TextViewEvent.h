//
//  TextViewEvent.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/9/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_TextViewEvent_h
#define glOMP_TextViewEvent_h

#include "ofMain.h"

class TextViewEvent : public ofEventArgs {
    
public:
    static ofEvent <TextViewEvent> events;

    std::string name;

    float x, y;
    std::string text;
    
    TextViewEvent() {}
};

#endif
