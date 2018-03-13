/*
 * CollisionManager.h
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "Rect.h"
#include "Circle.h"
#include "Point.h"
#include <stdio.h>

class CollisionManager {
private:
	static bool checkRectRectCollision(Rect* r1, Rect* r2);
	static bool checkCircleRectCollision(Circle* c, Rect* r);
	static bool checkCircleCircleCollision(Circle* c1, Circle* c2);

public:
	static bool checkCollision(Shape* s1, Shape* s2);
};

#endif /* COLLISIONMANAGER_H_ */
