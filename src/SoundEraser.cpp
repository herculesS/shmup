/*
 * soundEraser.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Hercules
 */

#include "SoundEraser.h"

std::queue<Sound*, std::deque<Sound*> > SoundEraser::soundsToErase;
Timer SoundEraser::waitToErase;
bool SoundEraser::queueEmpty = true;

void SoundEraser::EraseSound(Sound* toErase) {
	soundsToErase.push(toErase);
	if (queueEmpty) {
		waitToErase.start(WAIT_TO_ERASE);
		queueEmpty = false;
	}
}
void SoundEraser::cleanUp() {
	while (!soundsToErase.empty()) {
		delete (soundsToErase.front());
		soundsToErase.pop();
	}
}
void SoundEraser::update() {
	if (soundsToErase.empty()) {
		queueEmpty = true;
	}
	if (!queueEmpty) {
		waitToErase.update();
		if (waitToErase.isDone()) {
			delete (soundsToErase.front());
			soundsToErase.pop();
			waitToErase.start(WAIT_TO_ERASE);
		}
	}
}

