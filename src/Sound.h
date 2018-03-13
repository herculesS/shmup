/*
 * Sound.h
 *
 *  Created on: 09/06/2013
 *      Author: vitor
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "Playable.h"
#include "SDLBase.h"
#include <string>

class Sound: public Playable {
private:
	int channel;
	Mix_Chunk* sound;

public:
	Sound(std::string fileName);
	virtual ~Sound();

	void play(int n);
	void setVolume(int vol);
	void stop();

};

#endif /* SOUND_H_ */
