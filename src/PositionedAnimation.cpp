/*
 * Explosion.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Hercules
 */

#include "PositionedAnimation.h"

PositionedAnimation::PositionedAnimation(Point position,
		Animation* explosionAnimation) {
	this->explosionAnimation = explosionAnimation;
	this->position = position;
}
void PositionedAnimation::update(double dt) {
	this->explosionAnimation->update(dt);
}
void PositionedAnimation::render(float cameraX, float cameraY) {
	this->explosionAnimation->render(position.getX(), position.getY(), 1,
			GameArea::getSurface());
}
bool PositionedAnimation::ended() {
	bool ended = this->explosionAnimation->isEnded();
	return ended;
}
void PositionedAnimation::setPosition(Point position) {
	this->position = position;
}
void PositionedAnimation::setX(float x) {
	this->position.setX(x);
}
void PositionedAnimation::setY(float y) {
	this->position.setY(y);
}
PositionedAnimation::~PositionedAnimation() {
	delete (explosionAnimation);
}

