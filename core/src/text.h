//
//  Text.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/28/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_text_h
#define glOMP_text_h

#include "ofMain.h"
#include "graphic.h"
#include <string>

namespace glomp {
namespace graphics {

class Text : public Graphic {
public:
    Text();
    ~Text();
    
    virtual void Draw();

    void set_font(ofTrueTypeFont *new_font);
    void set_text(const char *text);
    void add_text(const char *text);
    
private:
    std::string _text;
    ofTrueTypeFont *_font;
    int _color;
    
    bool _word_wrap;
    bool _multi_line;
};

}
}

#endif
