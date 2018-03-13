/*
 * Vector2.cpp
 *
 *  Created on: 27/04/2013
 *      Author: Vitor
 */

#include "Vector2.h"

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::add(Vector2 vecToAdd) {
	Vector2 toReturn;

	toReturn.setX(this->getX() + vecToAdd.getX());
	toReturn.setY(this->getY() + vecToAdd.getY());

	return toReturn;

}

float Vector2::dotProduct(Vector2 vecToMult) {
	float toReturn = 0;

	toReturn = this->getX() * vecToMult.getX()
			+ this->getY() * vecToMult.getY();

	return toReturn;
}

Vector2 Vector2::constantProduct(float toMult) {
	Vector2 toReturn;

	toReturn.setX(this->getX() * toMult);
	toReturn.setY(this->getY() * toMult);

	return toReturn;
}

float Vector2::length() {
	return sqrt((this->getX() * this->getX()) + (this->getY() * this->getY()));
}

float Vector2::lengthSquared() {
	return (this->getX() * this->getX()) + (this->getY() * this->getY());
}

Vector2 Vector2::normalize() {
	Vector2 toReturn;

	toReturn.setX(this->getX() / this->length());
	toReturn.setY(this->getY() / this->length());

	return toReturn;

}

Vector2 Vector2::normalVector() {
	return rotateVector(90);
}

Vector2 Vector2::rotateVector(float angleInDegrees) {
	float angleInRadians = angleInDegrees * M_PI / 180;

	return Vector2(x * cos(angleInRadians) - y * sin(angleInRadians),
			x * sin(angleInRadians) + y * cos(angleInRadians));
}
