/*
 * Music.h
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#ifndef Music_H_
#define Music_H_

#include <string>
#include "SDLBase.h"
#include "Playable.h"

class Music: public Playable {
private:
	Mix_Music* music;
	int musicFadeOutInMs;

public:
	Music(std::string fileName);
	virtual ~Music();
	void play(int n);
	void stop();
	void pause();
	void unpause();
	void setVolume(int volume);

	int getMusicFadeOutInMs() const {
		return musicFadeOutInMs;
	}

	void setMusicFadeOutInMs(int musicFadeOutInMs) {
		this->musicFadeOutInMs = musicFadeOutInMs;
	}
};

#endif /* Music_H_ */
