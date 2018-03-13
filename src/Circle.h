/*
 * Circle.h
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"

class Circle: public Shape {
private:
	float radius;

public:
	Circle(float x, float y, float radius);
	Circle(Point center, float radius);
	virtual ~Circle();

	Shape::TYPE getType() {
		return Shape::CIRCLE;
	}

	void setX(float x) {
		center.setX(x);
	}

	void setY(float y) {
		center.setY(y);
	}

	float getX() {
		return center.getX();
	}

	float getY() {
		return center.getY();
	}

	float getRadius() const {
		return radius;
	}

	void setRadius(float radius) {
		this->radius = radius;
	}
};

#endif /* CIRCLE_H_ */
