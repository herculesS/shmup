/*
 * Droppable.cpp
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#include "Droppable.h"

Droppable::Droppable(Shape* shape, Sprite* dropSprite, Vector2 velocity) :
		GameObject(shape) {
	this->velocity = velocity;
	this->dropSprite = dropSprite;
	this->dead = false;
}

Droppable::~Droppable() {
	// TODO Auto-generated destructor stub
}

int Droppable::update(double dt) {

	this->velocity.setY(this->velocity.getY() + ACCELERATION * dt);

	this->shape->setY(
			this->shape->getY()
					+ std::min(velocity.getY(), (float) MAX_FALL_SPEED) * dt);

	return 0;
}

void Droppable::render(float cameraX, float cameraY) {

	dropSprite->render(shape->getX(), shape->getY(), true,
			GameArea::getSurface());

}

void Droppable::onCollisionWithPlayer(Player* player) {
	setDead(true);
}
