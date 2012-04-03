/*
 * Timer.h
 *
 *  Created on: Apr 2, 2012
 *      Author: jgraves
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

namespace glomp {

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    double elapsed(bool reset = true);
    double elapsedTimeInMicroSec(bool reset = true);

private:
    double startTimeInMicroSec;
    double endTimeInMicroSec;
    int    stopped;

    #ifdef WIN32
        LARGE_INTEGER frequency;
        LARGE_INTEGER startCount;
        LARGE_INTEGER endCount;
    #else
        timeval startCount;
        timeval endCount;
    #endif
};

} /* namespace glomp */
#endif /* TIMER_H_ */
