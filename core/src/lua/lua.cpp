//
//  lua_wrapper.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/27/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "lua_wrapper.h"

CFBundleRef mainBundle;

char file_name_buffer[1024];

bool platform_init() {
    mainBundle = CFBundleGetMainBundle();

    if(!mainBundle)
        return false;
    
    return true;
}

bool platform_builtin_file_path(std::string &output, const char *name_of_file_in_bundle) {
    CFURLRef resourceURL;

    // Look for the resource in the main bundle by name and type.
    CFStringRef cf_file_name = CFStringCreateWithCString(NULL, name_of_file_in_bundle, kCFStringEncodingASCII);
    resourceURL = CFBundleCopyResourceURL(mainBundle, cf_file_name, NULL, NULL);
    
    if(!resourceURL) {
        std::cerr << "Failed to locate a file in the loaded bundle!\n";
        return false;
    }
    
    if(!CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)file_name_buffer, 200)) {
        std::cerr << "Failed to turn a bundle resource URL into a filesystem path representation!\n";
        return false;
    }
    
    output = file_name_buffer;
    
    return true;
}

void platform_print_directory_contents(const char *dir) {
    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(dir);
    
    while((DirEntry=readdir(Dir))) {
        std::cout << DirEntry->d_name << "\n";
    }
}