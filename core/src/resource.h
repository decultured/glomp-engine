//
//  resource.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_resource_h
#define glOMP_resource_h

#include <string>

namespace glomp {

class Resource {
public:    
    std::string name; 

    Resource(const char *_name = "steve");
    virtual ~Resource();
        
private:
    
};

}

#endif
