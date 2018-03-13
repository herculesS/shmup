/*
 * Shape.cpp
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#include "Shape.h"

Shape::Shape() {
	this->center = Point(0, 0);
}

Shape::Shape(Point center) {
	this->center = center;
}

Shape::Shape(float x, float y) {
	this->center.setX(x);
	this->center.setY(y);
}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

