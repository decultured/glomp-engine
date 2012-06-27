//
//  logging.h
//  glOMP
//
//  Created by Jeffrey Graves on 6/26/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#ifndef glOMP_logging_h
#define glOMP_logging_h

#include <string>
#include <deque>

namespace glomp {
namespace util {

class Logger {
public:
    std::deque<std::string> messages;
    
    Logger();
    ~Logger();
    void log(const char *message);
    void print_to_file(const char *filename);

};    

}
}

#endif
