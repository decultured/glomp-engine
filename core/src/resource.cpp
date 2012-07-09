//  Mac OS X Platform specific code
//
//  platform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "resource.h"

namespace glomp {

Resource::Resource(const char *_name) {
    name = _name;
}

Resource::~Resource() {
    
}

}