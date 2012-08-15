//
//  platform.h
//  glomp
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glomp_platform_h
#define glomp_platform_h

namespace glomp {

    bool platform_init();
    bool platform_builtin_file_path(std::string &output, const char *name_of_file_in_bundle);
    void platform_print_directory_contents(const char *dir);

}

#endif
