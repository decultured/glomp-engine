//
//  text_view_event.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/9/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_text_view_event_h
#define glOMP_text_view_event_h

#include "ofMain.h"
#include "Poco/Delegate.h"

class TextViewEvent : public ofEventArgs {
    
public:
    static ofEvent <TextViewEvent> events;

    std::string name;

    float x, y;
    std::string text;
    
    TextViewEvent() {}
};

#endif
