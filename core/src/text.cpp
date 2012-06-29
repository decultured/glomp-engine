//  Mac OS X Platform specific code
//
//  platform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "text.h"

Text::Text() {
    font = NULL;
}

Text::~Text() {
    
}

void Text::Draw() {
    if (font && text.length())
        font->drawString(text, 0, 0);
}

void Text::set_font(ofTrueTypeFont *new_font) {
    font = new_font;
}

void Text::set_text(const char *text) {
    this->text = text;
}
