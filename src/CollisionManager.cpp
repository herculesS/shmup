/*
 * CollisionManager.cpp
 *
 *  Created on: 25/06/2013
 *      Author: Vitor
 */

#include "CollisionManager.h"

bool CollisionManager::checkCollision(Shape* s1, Shape* s2) {

	switch (s1->getType()) {
	case Shape::RECTANGLE:
		switch (s2->getType()) {
		case Shape::RECTANGLE:
			return checkRectRectCollision((Rect*) s1, (Rect*) s2);
			break;
		case Shape::CIRCLE:
			return checkCircleRectCollision((Circle*) s2, (Rect*) s1);
			break;
		}
		break;
	case Shape::CIRCLE:
		switch (s2->getType()) {
		case Shape::RECTANGLE:
			return checkCircleRectCollision((Circle*) s1, (Rect*) s2);
			break;
		case Shape::CIRCLE:
			return checkCircleCircleCollision((Circle*) s1, (Circle*) s2);
			break;
		}
		break;
	}

	return false;

}

bool CollisionManager::checkRectRectCollision(Rect* r1, Rect* r2) {
	return r1->collidesWith(*r2);
}

bool CollisionManager::checkCircleCircleCollision(Circle* c1, Circle* c2) {
	return c1->getCenterRef()->distance(*(c2->getCenterRef()))
			< (c1->getRadius() + c2->getRadius());
}

bool CollisionManager::checkCircleRectCollision(Circle* c, Rect* r) {

	Point rotatedCircleCenter = Point(c->getX() - r->getX(),
			c->getY() - r->getY()).rotate(-r->getAngleInDegrees()).addPoint(
			*r->getCenterRef());

	Point closestPoint = rotatedCircleCenter;

	float rectMinX = r->getX() - (r->getW() / 2);
	float rectMaxX = r->getX() + (r->getW() / 2);
	float rectMinY = r->getY() - (r->getH() / 2);
	float rectMaxY = r->getY() + (r->getH() / 2);

	if (rotatedCircleCenter.getX() < rectMinX) {
		closestPoint.setX(rectMinX);
	} else if (rotatedCircleCenter.getX() > rectMaxX) {
		closestPoint.setX(rectMaxX);
	}

	if (rotatedCircleCenter.getY() < rectMinY) {
		closestPoint.setY(rectMinY);
	} else if (rotatedCircleCenter.getY() > rectMaxY) {
		closestPoint.setY(rectMaxY);
	}

	if (closestPoint.distanceSquared(rotatedCircleCenter)
			> (c->getRadius() * c->getRadius()))
		return false;

	return true;
}
