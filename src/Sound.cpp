/*
 * Sound.cpp
 *
 *  Created on: 09/06/2013
 *      Author: vitor
 */

#include "Sound.h"

Sound::Sound(std::string fileName) {
	this->fileName = fileName;
	this->sound = Mix_LoadWAV(fileName.c_str());
	this->channel = -1;

	if (!sound) {
		fprintf(stderr, "Nao consegui carregar o som %s.\n", fileName.c_str());
		exit(1);
	}
}

Sound::~Sound() {
	Mix_FreeChunk(sound);
}
void Sound::setVolume(int vol) {
	Mix_VolumeChunk(sound, vol);
}

void Sound::play(int n) {
	if (sound)
		channel = Mix_PlayChannel(channel, sound, n - 1);
}

void Sound::stop() {
	if (sound)
		Mix_HaltChannel(channel);
}
