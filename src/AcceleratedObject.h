/*
 * AcceleratedObject.h
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#ifndef ACCELERATEDOBJECT_H_
#define ACCELERATEDOBJECT_H_

#include "GameObject.h"
#include "Animation.h"
#include "Vector2.h"
#include "InputManager.h"
#include <math.h>

class AcceleratedObject: public GameObject {
protected:
	Animation* animation;
	float speed;
	float acceleration;
	float rotation;
	Vector2 vecSpeed;
	Vector2 vecAccel;
	int hitPoints;

public:
	AcceleratedObject(Animation* animation, Shape* shape, int hitPoints);
	virtual ~AcceleratedObject();

	void render(float cameraX, float cameraY);
	int update(double dt);

	int getHitPoints() const {
		return hitPoints;
	}

	void setHitPoints(int hitPoints) {
		this->hitPoints = hitPoints;
	}
};

#endif /* ACCELERATEDOBJECT_H_ */
