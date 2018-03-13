/*
 * Animation.cpp
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#include "Animation.h"

Animation::Animation(std::string fileName, int frameTimeInMilliseconds,
		int numRows, int* numberOfSpritesInEachRow, int spriteWidth,
		bool repeat) :
		Sprite(fileName) {
	this->frameTimeInMilliseconds = frameTimeInMilliseconds;
	this->numRows = numRows;
	this->timeInMilliseconds.start(frameTimeInMilliseconds);
	this->currentRow = 0;
	this->currentFrame = 0;
	this->ended = false;
	this->repeat = repeat;
	for (int i = 0; i < numRows; i++) {
		this->numberOfSpritesInEachRow[i] = numberOfSpritesInEachRow[i];
	}

	this->spriteWidth = spriteWidth;
	this->spriteHeight = this->spriteSurface->h / numRows;

	this->clipRect.w = spriteWidth;
	this->clipRect.h = this->spriteSurface->h / numRows;

}

bool Animation::isEnded() {
	return ended;
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

void Animation::update(double dt) {
	if (!ended) {
		timeInMilliseconds.update();
		if (timeInMilliseconds.isDone()) {
			timeInMilliseconds.start(frameTimeInMilliseconds);
			if (currentFrame >= numberOfSpritesInEachRow[currentRow]) {
				if (!repeat) {
					ended = true;
				} else {
					currentFrame = 0;
				}
			}
			clipRect.x = clipRect.w * currentFrame;
			clipRect.y = clipRect.h * currentRow;
			if (clipRect.x >= spriteSurface->w) {
				clipRect.x = (clipRect.x - spriteSurface->w) % spriteSurface->w;
			}
			clip(clipRect.x, clipRect.y, clipRect.w, clipRect.h);
			currentFrame++;
		}
	}
}

void Animation::reset() {
	ended = false;
	currentFrame = 0;
}

void Animation::setFrame(int frame) {
	clipRect.x = clipRect.w * frame;
}

void Animation::setCurrentRow(int row) {
	this->currentRow = row;
}

void Animation::render(int x, int y, bool center, SDL_Surface *destSurf) {
	if (!ended) {
		Sprite::render(x, y, center, destSurf);
	}
}

