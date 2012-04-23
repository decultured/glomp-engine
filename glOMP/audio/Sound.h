/*
 * Sound.h
 *
 *  Created on: Apr 19, 2012
 *      Author: jgraves
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "Audio.h"

namespace glomp {
namespace audio {

class Sound {
private:
	float velocity[3];
	float position[3];

	ALsizei size,freq;
	ALvoid  *data;

	//Is the name of source (where the sound come from)
    ALuint source;
    //Stores the sound data
    ALuint buffer;
    //The Sample Rate of the WAVE file
    ALuint frequency;
    //The audio format (bits per sample, number of channels)
    ALenum format;

    bool playing;
public:
	Sound();
	virtual ~Sound();
	bool load_wav(const char *filename);
	void play();
	void stop();
	void play_loop();
};

} /* namespace audio */
} /* namespace glomp */
#endif /* SOUND_H_ */
