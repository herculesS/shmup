/*
 * Point.cpp
 *
 *  Created on: 01/05/2013
 *      Author: Vitor
 */

#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

Point::~Point() {
}

float Point::distance(Point from) {
	return sqrt(
			pow(this->getX() - from.getX(), 2)
					+ pow(this->getY() - from.getY(), 2));
}

float Point::distanceSquared(Point from) {
	return pow(this->getX() - from.getX(), 2)
			+ pow(this->getY() - from.getY(), 2);
}

Point Point::addVector(Vector2 toAdd) {
	return Point(this->getX() + toAdd.getX(), this->getY() + toAdd.getY());
}

Point Point::addPoint(Point toAdd) {
	return Point(this->getX() + toAdd.getX(), this->getY() + toAdd.getY());
}

float Point::dotProduct(Vector2 toMult) {
	return x * toMult.getX() + y * toMult.getY();
}

// A operação cria um vetor da seguinte maneira:
// (x - toSubtract.x, y - toSubtract.y)
// Portanto o objeto é o ponto final e o parâmetro o ponto inicial
Vector2 Point::createVector(Point initialPoint) {
	return Vector2(x - initialPoint.getX(), y - initialPoint.getY());
}

Point Point::projectOnVector(Vector2 projectionAxis) {
	float projectionConstant = this->dotProduct(projectionAxis)
			/ projectionAxis.lengthSquared();

	return Point(projectionConstant * projectionAxis.getX(),
			projectionConstant * projectionAxis.getY());
}

Point Point::rotate(float angleInDegrees) {
	float angleInRadians = angleInDegrees * M_PI / 180;

	return Point(x * cos(angleInRadians) + y * sin(angleInRadians),
			-x * sin(angleInRadians) + y * cos(angleInRadians));
}
