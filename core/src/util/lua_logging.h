//
//  platform.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_lua_logging_h
#define glOMP_lua_logging_h

bool platform_init();
bool platform_builtin_file_path(std::string &output, const char *name_of_file_in_bundle);
void platform_print_directory_contents(const char *dir);

#endif
