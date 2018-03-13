/*
 * FollowerObject.cpp
 *
 *  Created on: 26/05/2013
 *      Author: Vitor
 */

#include "FollowerObject.h"

FollowerObject::FollowerObject(Sprite* sprite, Shape* shape) :
		GameObject(shape) {
	this->sprite = sprite;
}

FollowerObject::~FollowerObject() {
	// TODO Auto-generated destructor stub
}

int FollowerObject::update(double dt) {

	int speedValue = 200;

	if (!coordinatesQueue.empty()) {
		Point target = coordinatesQueue.front();

		speed.setX(target.getX() - shape->getCenterRef()->getX());
		speed.setY(target.getY() - shape->getCenterRef()->getY());
		speed = speed.normalize();
		speed = speed.constantProduct(speedValue);

		if (shape->getCenterRef()->distance(target) < 10) {
			coordinatesQueue.pop();
		}

	} else {
		speed.setX(0);
		speed.setY(0);
	}

	shape->getCenterRef()->setX(
			shape->getCenterRef()->getX() + speed.getX() * dt);
	shape->getCenterRef()->setY(
			shape->getCenterRef()->getY() + speed.getY() * dt);

	return 0;
}

void FollowerObject::render(float cameraX, float cameraY) {
	if (sprite)
		sprite->render(shape->getCenterRef()->getX() - cameraX,
				shape->getCenterRef()->getY() - cameraY, true);

	renderQueueLines(cameraX, cameraY);
}

void FollowerObject::renderQueueLines(float cameraX, float cameraY) {

	Point temp;
	Point temp2;
	std::queue<Point> tempQueue;

	if (!coordinatesQueue.empty()) {
		temp = coordinatesQueue.front();
		coordinatesQueue.pop();

		SDLBase::drawLine(temp.getX() - cameraX, temp.getY() - cameraY,
				shape->getCenterRef()->getX() - cameraX,
				shape->getCenterRef()->getY() - cameraY, 0x00FFFFFF, 10);

		tempQueue.push(temp);

		while (!coordinatesQueue.empty()) {
			temp2 = coordinatesQueue.front();
			coordinatesQueue.pop();

			SDLBase::drawLine(temp2.getX() - cameraX, temp2.getY() - cameraY,
					temp.getX() - cameraX, temp.getY() - cameraY, 0x00FFFFFF,
					10);

			tempQueue.push(temp2);

			temp = temp2;
		}

		coordinatesQueue = tempQueue;

	}

}

void FollowerObject::enqueueCommand(Point position) {
	coordinatesQueue.push(position);
}
