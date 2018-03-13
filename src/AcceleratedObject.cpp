/*
 * AcceleratedObject.cpp
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#include "AcceleratedObject.h"

AcceleratedObject::AcceleratedObject(Animation* animation, Shape* shape,
		int hitPoints) :
		GameObject(shape) {
	this->animation = animation;
	this->hitPoints = hitPoints;

	speed = acceleration = rotation = 0;

}

void AcceleratedObject::render(float cameraX, float cameraY) {
	animation->render(shape->getCenterRef()->getX() - cameraX,
			shape->getCenterRef()->getY() - cameraY, true);
}

int AcceleratedObject::update(double dt) {

	acceleration = 0;
	animation->setFrameTime(200);

	if (InputManager::getInstance()->isKeyPressed(SDLK_d)) {
		rotation -= 80 * dt;
	}
	if (InputManager::getInstance()->isKeyPressed(SDLK_a)) {
		rotation += 80 * dt;
	}
	if (InputManager::getInstance()->isKeyPressed(SDLK_w)) {
		acceleration = 80;
		animation->setFrameTime(6);
	}
	if (InputManager::getInstance()->isKeyPressed(SDLK_s))
		acceleration = -80;

	speed += acceleration * dt;

	vecAccel.setX(-cos((rotation - 90) * M_PI / 180));
	vecAccel.setY(sin((rotation - 90) * M_PI / 180));

	vecSpeed.setX(-cos((rotation - 90) * M_PI / 180));
	vecSpeed.setY(sin((rotation - 90) * M_PI / 180));

	vecAccel = vecAccel.constantProduct(acceleration);
	vecSpeed = vecSpeed.constantProduct(speed);

	shape->getCenterRef()->setX(
			shape->getCenterRef()->getX() + vecSpeed.getX() * dt);
	shape->getCenterRef()->setY(
			shape->getCenterRef()->getY() + vecSpeed.getY() * dt);

	animation->update(dt);
	animation->rotoZoom(rotation, 1, 1, false);

	return 0;
}

AcceleratedObject::~AcceleratedObject() {
	// TODO Auto-generated destructor stub
}

