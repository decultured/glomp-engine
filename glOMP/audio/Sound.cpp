/*
 * Sound.cpp
 *
 *  Created on: Apr 19, 2012
 *      Author: jgraves
 */

#include "Sound.h"
#include <iostream>

namespace glomp {
namespace audio {

Sound::Sound() {
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;

	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;

	format = 0;
}

Sound::~Sound() {
	//Delete the OpenAL Source
    alDeleteSources(1, &source);

    //Delete the OpenAL Buffer
    alDeleteBuffers(1, &buffer);
}

bool Sound::load_wav(const char *filename) {
    //Loading of the WAVE file
    FILE *fp = 0;
    fp = fopen("Sound.wav", "rb");
    if (!fp) {
    	std::cerr << "Failed to open file";
    	return false;
    }

    //Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    unsigned int size,chunkSize;
    short formatType,channels;
    unsigned int sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    unsigned int dataSize;

    //Check that the WAVE file is OK
    fread(type,sizeof(char),4,fp);
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F') {
    	std::cerr << "Not RIFF";
    	return false;
    }

    fread(&size, sizeof(unsigned int),1,fp);
    fread(type, sizeof(char),4,fp);
    if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E') {
    	std::cerr << "Not WAVE";
    	return false;
    }

    fread(type,sizeof(char),4,fp);
    if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ') {
    	std::cerr << "Not FMT";
    	return false;
    }

    //Now we know that the file is a acceptable WAVE file
    //Info about the WAVE data is now read and stored
    fread(&chunkSize,sizeof(unsigned int),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&sampleRate,sizeof(unsigned int),1,fp);
    fread(&avgBytesPerSec,sizeof(unsigned int),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);

    fread(type,sizeof(char),4,fp);
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a') {
    	std::cerr << "Missing DATA";
    	return false;
    }

    //The size of the sound data is read
    fread(&dataSize,sizeof(unsigned int),1,fp);

    //Display the info about the WAVE file
    std::cout << "Chunk Size: " << chunkSize << "\n";
    std::cout << "Format Type: " << formatType << "\n";
    std::cout << "Channels: " << channels << "\n";
    std::cout << "Sample Rate: " << sampleRate << "\n";
    std::cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
    std::cout << "Bytes Per Sample: " << bytesPerSample << "\n";
    std::cout << "Bits Per Sample: " << bitsPerSample << "\n";
    std::cout << "Data Size: " << dataSize << "\n";

    unsigned char* file_buffer= new unsigned char[dataSize];
    std::cout << fread(file_buffer, sizeof(unsigned char), dataSize, fp) << " bytes loaded\n";

    fclose(fp);

    frequency = sampleRate;

	//Generate one OpenAL Buffer and link to "buffer"
	alGenBuffers(1, &buffer);

	//Generate one OpenAL Source and link to "source"
	alGenSources(1, &source);

	//Error during buffer/source generations
	if(alGetError() != AL_NO_ERROR) {
		std::cerr << "Error GenSource";
		return false;
	}

	//Figure out the format of the WAVE file
	if(bitsPerSample == 8)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO8;
		else if(channels == 2)
			format = AL_FORMAT_STEREO8;
	}
	else if(bitsPerSample == 16)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO16;
		else if(channels == 2)
			format = AL_FORMAT_STEREO16;
	}
	if(!format) {
		std::cerr << "Wrong BitPerSample";
		return false;
	}

	//Store the sound data in the OpenAL Buffer
    alBufferData(buffer, format, file_buffer, dataSize, frequency);
    if(alGetError() != AL_NO_ERROR) {
    	std::cerr << "Error loading ALBuffer";
    	return false;
    }

    //Link the buffer to the source
    alSourcei (source, AL_BUFFER,   buffer);
    //Set the pitch of the source
    alSourcef (source, AL_PITCH, 1.0f);
    //Set the gain of the source
    alSourcef (source, AL_GAIN, 1.0f);
    //Set the position of the source
    alSourcefv(source, AL_POSITION, position);
    //Set the velocity of the source
    alSourcefv(source, AL_VELOCITY, velocity);
    //Set if source is looping sound
    alSourcei (source, AL_LOOPING,  AL_FALSE);

    return true;
}

void Sound::play() {
    //PLAY
    alSourcePlay(source);
    if(alGetError() != AL_NO_ERROR) {
    	std::cerr << "Error playing sound";
    }
}

} /* namespace audio */
} /* namespace glomp */
