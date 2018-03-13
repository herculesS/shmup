/*
 * Animation.h
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Sprite.h"
#include <string>
#include "Timer.h"
#include <algorithm>

class Animation: public Sprite {
private:
	int numberOfSpritesInEachRow[15];
	int numRows;
	int currentRow;
	int spriteWidth;
	int spriteHeight;
	Timer timeInMilliseconds;
	int currentFrame;
	int frameTimeInMilliseconds;
	bool repeat;
	bool ended;

public:
	Animation(std::string fileName, int frameTimeInMilliseconds, int numRows,
			int* numberOfSpritesInEachRow, int spriteWidth, bool repeat);
	virtual ~Animation();

	void update(double dt);
	void render(int x, int y, bool center, SDL_Surface *destSurf =
			SDLBase::getScreen());
	void reset();
	void setFrame(int frame);
	void setCurrentRow(int row);
	bool isEnded();

	int getFrameTime() const {
		return frameTimeInMilliseconds;
	}

	void setFrameTime(int frameTime) {
		this->frameTimeInMilliseconds = std::max(1, frameTime);
	}

};

#endif /* ANIMATION_H_ */
