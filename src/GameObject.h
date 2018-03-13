/*
 * GameObject.h
 *
 *  Created on: 17/05/2013
 *      Author: vitor
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Point.h"
#include "Shape.h"
#include <math.h>
#include <stdio.h>

class GameObject {
protected:
	Shape* shape;

public:
	GameObject(Shape* shape);
	virtual int update(double dt) = 0;
	virtual void render(float cameraX = 0, float cameraY = 0) = 0;
	virtual ~GameObject();

	Shape* getShape() {
		return shape;
	}
};

#endif /* GAMEOBJECT_H_ */
