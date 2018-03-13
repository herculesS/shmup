/*
 * Circle.cpp
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#include "Circle.h"

Circle::Circle(float x, float y, float radius) :
		Shape(x, y) {
	this->radius = radius;

}

Circle::Circle(Point center, float radius) :
		Shape(center) {
	this->radius = radius;
}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

