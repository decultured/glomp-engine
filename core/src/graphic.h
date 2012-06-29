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
    
private:
    virtual void PreDraw();
    virtual void Draw();
    virtual void PostDraw();

    std::list<Graphic *> children;
    std::list<Graphic *>::iterator draw_iter;

    float x, y, rot;
};


#endif
