/*
 * BombManager.cpp
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#include "BombManager.h"

Bomb* BombManager::bomb = NULL;

void BombManager::instantiateBomb(Point position) {
	if (bomb) {
		delete (bomb);
	}
	bomb = new Bomb(position);
}

void BombManager::update(double dt) {
	if (bomb) {
		bomb->update(dt);
		if (bomb->isFinished()) {
			delete (bomb);
			bomb = NULL;
		}
	}
}

bool BombManager::checkCollision(GameObject* toCheck) {
	if (bomb) {
		return CollisionManager::checkCollision(bomb->getShape(),
				toCheck->getShape());
	}

	return false;
}

Bomb* BombManager::getBomb() {
	return bomb;
}
