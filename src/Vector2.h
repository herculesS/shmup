/*
 * Vector2.h
 *
 *  Created on: 27/04/2013
 *      Author: Vitor
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <math.h>

class Vector2 {
private:
	float x, y;

public:
	Vector2();
	Vector2(float x, float y);
	virtual ~Vector2();

	Vector2 add(Vector2 vecToAdd);
	float dotProduct(Vector2 vecToMult);
	Vector2 normalize();
	Vector2 constantProduct(float toMult);
	float length();
	float lengthSquared();
	Vector2 normalVector();
	Vector2 rotateVector(float angleInDegrees);

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

#endif /* VECTOR2_H_ */
