/*
 * Rect.cpp
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#include "Rect.h"

Rect::Rect() {
	w = 0;
	h = 0;
	angleInDegrees = 0;
}

Rect::Rect(float x, float y, float w, float h, float angleInDegrees) :
		Shape(x, y) {
	this->w = w;
	this->h = h;
	this->angleInDegrees = angleInDegrees;
	calculatePoints();
}

Rect::Rect(Point center, float w, float h, float angleInDegrees) :
		Shape(center) {
	this->w = w;
	this->h = h;
	this->angleInDegrees = angleInDegrees;
	calculatePoints();
}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}

bool Rect::collidesWith(Rect other) {

	Vector2 axisVector[4];

	axisVector[0] = getTLTRNormal();
	axisVector[1] = getTRBRNormal();
	axisVector[2] = other.getTLTRNormal();
	axisVector[3] = other.getTRBRNormal();

	for (int i = 0; i < 4; i++) {
		if (other.minProjection(axisVector[i])
				> this->maxProjection(axisVector[i])
				|| other.maxProjection(axisVector[i])
						< this->minProjection(axisVector[i])) {
			return false;
		}
	}

	return true;

}

void Rect::setH(float h) {
	this->h = std::max((float) 0, h);
	calculatePoints();
}

void Rect::setW(float w) {
	this->w = std::max((float) 0, w);
	calculatePoints();
}

void Rect::setCenter(Point position) {
	this->center = position;
	calculatePoints();
}

void Rect::setX(float x) {
	center.setX(x);
	calculatePoints();
}

void Rect::setY(float y) {
	center.setY(y);
	calculatePoints();
}

void Rect::setAngleInDegrees(float angleInDegrees) {
	this->angleInDegrees = angleInDegrees;
	calculatePoints();
}

void Rect::calculatePoints() {
	rotatedTopLeft = Point(-w / 2, -h / 2).rotate(angleInDegrees).addPoint(
			center);
	rotatedTopRight = Point(w / 2, -h / 2).rotate(angleInDegrees).addPoint(
			center);
	rotatedBottomRight = Point(w / 2, h / 2).rotate(angleInDegrees).addPoint(
			center);
	rotatedBottomLeft = Point(-w / 2, h / 2).rotate(angleInDegrees).addPoint(
			center);

	TLTRNormal = rotatedTopRight.createVector(rotatedTopLeft).normalVector();
	TRBRNormal =
			rotatedBottomRight.createVector(rotatedTopRight).normalVector();
}

float Rect::minProjection(Vector2 projectionAxis) {
	float minProjection = rotatedTopLeft.dotProduct(projectionAxis);

	if (minProjection > rotatedTopRight.dotProduct(projectionAxis))
		minProjection = rotatedTopRight.dotProduct(projectionAxis);
	if (minProjection > rotatedBottomRight.dotProduct(projectionAxis))
		minProjection = rotatedBottomRight.dotProduct(projectionAxis);
	if (minProjection > rotatedBottomLeft.dotProduct(projectionAxis))
		minProjection = rotatedBottomLeft.dotProduct(projectionAxis);

	return minProjection;
}

float Rect::maxProjection(Vector2 projectionAxis) {
	float maxProjection = rotatedTopLeft.dotProduct(projectionAxis);

	if (maxProjection < rotatedTopRight.dotProduct(projectionAxis))
		maxProjection = rotatedTopRight.dotProduct(projectionAxis);
	if (maxProjection < rotatedBottomRight.dotProduct(projectionAxis))
		maxProjection = rotatedBottomRight.dotProduct(projectionAxis);
	if (maxProjection < rotatedBottomLeft.dotProduct(projectionAxis))
		maxProjection = rotatedBottomLeft.dotProduct(projectionAxis);

	return maxProjection;
}
