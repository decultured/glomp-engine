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


Logger::Logger() {
    
}

Logger::~Logger() {
    release_iostream();
}

void Logger::capture_iostream() {
    old_cout = std::cout.rdbuf(buffer.rdbuf());
    old_cerr = std::cerr.rdbuf(buffer.rdbuf());
}

void Logger::release_iostream() {
    std::cout.rdbuf(old_cout);
    std::cerr.rdbuf(old_cerr);
}

void Logger::log(const char *message) {
    buffer << message;
}

std::string Logger::get_buffer() {
    return buffer.str();
}

void Logger::clear() {
    buffer.str("");
}

}
}