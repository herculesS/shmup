/*
 * DropManager.cpp
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#include "DropManager.h"

std::vector<Droppable*> DropManager::dropVector;

void DropManager::update(double dt) {
	for (std::vector<Droppable*>::iterator it = dropVector.begin();
			it != dropVector.end(); ++it) {
		(*it)->update(dt);

		if ((*it)->isDead()) {
			delete (*it);
			it = dropVector.erase(it);
			it--;
		}

	}
}

void DropManager::render(float cameraX, float cameraY) {
	for (std::vector<Droppable*>::iterator it = dropVector.begin();
			it != dropVector.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}
}

void DropManager::cleanUp() {

	for (std::vector<Droppable*>::iterator it = dropVector.begin();
			it != dropVector.end(); ++it) {
		delete (*it);
		it = dropVector.erase(it);
		it--;
	}

}

void DropManager::insertDrops(std::vector<Droppable*> toInsert) {
	dropVector.insert(dropVector.end(), toInsert.begin(), toInsert.end());
}

Droppable* DropManager::checkCollision(GameObject* toCollide) {

	for (std::vector<Droppable*>::iterator it = dropVector.begin();
			it != dropVector.end(); ++it) {
		if (CollisionManager::checkCollision((*it)->getShape(),
				toCollide->getShape())) {
			return (*it);
		}
	}

	return NULL;
}

void DropManager::removeOffScreenDrops(float areaWidth, float areaHeight) {

	for (std::vector<Droppable*>::iterator it = dropVector.begin();
			it != dropVector.end(); ++it) {
		if (!valueInRange((*it)->getShape()->getX(), -150, areaWidth)
				|| !valueInRange((*it)->getShape()->getY(), -150, areaHeight)) {
			delete (*it);
			it = dropVector.erase(it);
			it--;
		}
	}

}

bool DropManager::valueInRange(float value, float min, float max) {
	return (value >= min) && (value <= max);
}
