/*
 * Audio.cpp
 *
 *  Created on: Apr 19, 2012
 *      Author: jgraves
 */

#include "Audio.h"
#include <iostream>

namespace glomp {
namespace audio {

Audio::Audio() {
	listenerPos[0] = 0.0;
	listenerPos[1] = 0.0;
	listenerPos[2] = 0.0;

	listenerVel[0] = 0.0;
	listenerVel[1] = 0.0;
	listenerVel[2] = 0.0;

	listenerOri[0] = 0.0;
	listenerOri[1] = 0.0;
	listenerOri[2] = 1.0;
	listenerOri[3] = 0.0;
	listenerOri[4] = 1.0;
	listenerOri[5] = 0.0;

	this->device = alcOpenDevice(NULL);

	if (!device) {
		std::cerr << "No Audio Device\n";
		return;
	}

	context = alcCreateContext(this->device, NULL);
	alcMakeContextCurrent(context);

	if (!context) {
		std::cerr << "No audio context";
		return;
	}

	alListenerfv(AL_POSITION,listenerPos);
	alListenerfv(AL_VELOCITY,listenerVel);
	alListenerfv(AL_ORIENTATION,listenerOri);


	ALuint source;
	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}


Audio::~Audio() {
    //Clean-up
    alcMakeContextCurrent(NULL);                                                //Make no context current
    alcDestroyContext(context);                                                 //Destroy the OpenAL Context
    alcCloseDevice(device);                                                     //Close the OpenAL Device
}

}
} /* namespace glomp */
