//  Mac OS X Platform specific code
//
//  platform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "text.h"

namespace glomp {


Text::Text() {
    _font = NULL;
    _color = 0x67E09D;
    _word_wrap = false;
    _multi_line = true;
}

Text::~Text() {
    
}

void Text::Draw() {
    if (!_font || !_text.length())
        return;
    
    ofSetHexColor(_color);
    
    ofTranslate(0, -this->height());
    _font->drawString(_text, 0, 0);
}

void Text::set_font(ofTrueTypeFont *new_font) {
    _font = new_font;
}

void Text::set_text(const char *text) {
    _text = text;
    ofRectangle rect = _font->getStringBoundingBox(_text, 0, 0);
    size(rect.width, rect.height);
}

void Text::add_text(const char *text) {
    set_text((_text + text).c_str());
}

}
