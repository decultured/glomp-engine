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
#include <sstream>

namespace glomp {
namespace util {

class Logger {
private:
    std::streambuf *old_cout;
    std::streambuf *old_cerr;
    std::stringbuf *old_clog;

public:
    std::stringstream buffer;
    
    Logger();
    ~Logger();
    
    void capture_iostream();
    void release_iostream();

    void log(const char *message);
    
    std::string get_buffer();
    void clear();
};    

}
}

#endif
