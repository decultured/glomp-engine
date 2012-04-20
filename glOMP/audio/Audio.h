/*
 * Audio.h
 *
 *  Created on: Apr 19, 2012
 *      Author: jgraves
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#define GLOMP_PLATFORM_OSX

typedef char ALboolean;
typedef char ALchar;
typedef char ALbyte;
typedef unsigned char ALubyte;
typedef short ALshort;
typedef unsigned short ALushort;
typedef int ALint;
typedef unsigned int ALuint;
typedef int ALsizei;
typedef int ALenum;
typedef float ALfloat;
typedef double ALdouble;
typedef void ALvoid;

#ifdef GLOMP_PLATFORM_OSX
// To resolve highlighting bug in eclipse, I explicitly include the framework folders here.
// TODO : find a better fix for this!
#include <alc.h>
#include <al.h>
#else
#include <AL/alc.h>
#include <AL/al.h>
#endif


namespace glomp {
namespace audio {

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

class Audio {
private:
	ALCdevice* device;
	ALCcontext* context;

	float listenerPos[3];//={0.0,0.0,4.0};
	float listenerVel[3];//={0.0,0.0,0.0};
	float listenerOri[6];//={0.0,0.0,1.0, 0.0,1.0,0.0};

	unsigned int buffer[NUM_BUFFERS];
	unsigned int source[NUM_SOURCES];
	unsigned int environment[NUM_ENVIRONMENTS];

public:
	Audio();
	virtual ~Audio();
};

}
} /* namespace glomp */
#endif /* AUDIO_H_ */
