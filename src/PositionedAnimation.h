/*
 * Explosion.h
 *
 *  Created on: Jul 11, 2013
 *      Author: Hercules
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_
#include "Animation.h"
#include "GameArea.h"

class PositionedAnimation {
private:
	Animation *explosionAnimation;
	Point position;
public:
	PositionedAnimation(Point position, Animation* explosionAnimation);
	void update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void setPosition(Point position);
	void setX(float x);
	void setY(float y);
	bool ended();
	virtual ~PositionedAnimation();
};

#endif /* EXPLOSION_H_ */
