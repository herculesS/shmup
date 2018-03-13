/*
 * Music.cpp
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#include "Music.h"

Music::Music(std::string fileName) {
	this->fileName = fileName;
	this->music = Mix_LoadMUS(fileName.c_str());
	this->musicFadeOutInMs = 0;

	if (!music) {
		fprintf(stderr, "Nao consegui carregar a musica %s.\n",
				fileName.c_str());
		exit(1);
	}

}

Music::~Music() {
	Mix_FreeMusic(music);
}

void Music::play(int n) {
	if (music) {
		Mix_PlayMusic(music, n);
	}
}

void Music::stop() {
	if (music) {
		Mix_FadeOutMusic(musicFadeOutInMs);
	}
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::unpause() {
	Mix_ResumeMusic();
}

// Varia de 0 a 128 (MIX_MAX_VOLUME)
void Music::setVolume(int volume) {
	Mix_VolumeMusic(volume);
}
