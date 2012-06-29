//
//  graphic.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/28/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_graphic_h
#define glOMP_graphic_h

#include "resource.h"
#include <list>

class Graphic : public Resource {
public:
    Graphic();
    ~Graphic();

    void Render();
    Graphic *add_child(Graphic *new_child);
    
    void position(float x, float y);
    void rotation(float rot);
    
    void size(float w, float h) { width = w; height = h; }
    
    float get_height() {return height;}
    float get_width() {return width;}
    
private:
    virtual void PreDraw();
    virtual void Draw();
    virtual void PostDraw();

    std::list<Graphic *> children;
    std::list<Graphic *>::iterator draw_iter;

    float x, y, rot, width, height;
};


#endif
