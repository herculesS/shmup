/*
 * soundEraser.h
 *
 *  Created on: Jul 25, 2013
 *      Author: Hercules
 */

#ifndef SOUNDERASER_H_
#define SOUNDERASER_H_
#include "Sound.h"
#include "Timer.h"
#include <queue>
#include <deque>
#define WAIT_TO_ERASE 5000
class SoundEraser {
private:
	static std::queue<Sound*, std::deque<Sound*> > soundsToErase;
	static Timer waitToErase;
	static bool queueEmpty;
public:
	static void EraseSound(Sound* toErase);
	static void cleanUp();
	static void update();
};

#endif /* SOUNDERASER_H_ */
