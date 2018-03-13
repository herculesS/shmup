/*
 * Shape.h
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Point.h"

class Shape {
protected:
	Point center;

public:
	Shape();
	Shape(Point center);
	Shape(float x, float y);
	virtual ~Shape();

	virtual void setX(float x) {
		center.setX(x);
	}

	virtual void setY(float y) {
		center.setX(y);
	}

	enum TYPE {
		RECTANGLE = 0, CIRCLE
	};

	virtual float getX() {
		return center.getX();
	}

	virtual float getY() {
		return center.getY();
	}

	Point* getCenterRef() {
		return &center;
	}

	virtual TYPE getType() = 0;

	virtual void setCenter(Point center) {
		this->center = center;
	}
};

#endif /* SHAPE_H_ */
