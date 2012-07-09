//
//  transform.h
//  glOMP
//
//  Created by Jeffrey Graves on 7/5/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_transform_h
#define glOMP_transform_h

namespace glomp {

class Transform {
private:
public:
    float x, y;
    float rotation;
    float scale_x, scale_y;
    
    Transform();
    ~Transform();
};

}

#endif
