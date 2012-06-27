//  Mac OS X Platform specific code
//
//  platform.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "logging.h"

#include <iostream>
#include <fstream>

namespace glomp {
namespace util {


Logger::Logger() {}

Logger::~Logger() {
    print_to_file("output.txt");
}

void Logger::log(const char *message) {
    this->messages.push_back(message);
    std::cout << message << std::endl;
}

void Logger::print_to_file(const char *filename) {
    std::ofstream out_file;
    out_file.open(filename);
    
    while (!messages.empty())
    {
        out_file << messages.front() << std::endl;
        std::cout << messages.front() << std::endl;
        messages.pop_front();
    }
    
    out_file.close();
}

}
}