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

namespace glomp {
namespace graphics {

class Graphic : public Resource {
public:
    Graphic();
    ~Graphic();

    void Render();
    Graphic *add_child(Graphic *new_child);
    
    virtual void position(float x, float y) { _x = x; _y = y; }
    virtual void rotation(float angle) { _rot = angle; }
    virtual void size(float width, float height) { _width = width; _height = height; }
    virtual void height(float height) { _height = height; }
    virtual void width(float width) { _width = width; }

    virtual float rotation() {return _rot;}
    virtual float x() {return _x;}
    virtual float y() {return _y;}
    virtual float height() {return _height;}
    virtual float width() {return _width;}
    
private:
    virtual void PreDraw();
    virtual void Draw();
    virtual void PostDraw();

    Graphic *_parent;
    std::list<Graphic *> _children;
    std::list<Graphic *>::iterator _draw_iter;

    float _x, _y, _rot, _width, _height, _x_scale, _y_scale;
};

}
}

#endif
