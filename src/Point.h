/*
 * Point.h
 *
 *  Created on: 01/05/2013
 *      Author: Vitor
 */

#ifndef POINT_H_
#define POINT_H_

#include <math.h>
#include "Vector2.h"

class Point {
private:
	float x;
	float y;

public:
	Point();
	Point(float x, float y);
	virtual ~Point();
	float distance(Point from);
	float distanceSquared(Point from);
	float dotProduct(Vector2 toMult);
	Point addVector(Vector2 toAdd);
	Point addPoint(Point toAdd);
	Vector2 createVector(Point initialPoint);
	Point projectOnVector(Vector2 projectionVector);
	Point rotate(float angleInDegrees);

	float getX() const {
		return x;
	}

	void setX(float x) {
		this->x = x;
	}

	float getY() const {
		return y;
	}

	void setY(float y) {
		this->y = y;
	}
};

#endif /* POINT_H_ */
