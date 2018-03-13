/*
 * Bomb.cpp
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#include "Bomb.h"

Bomb::Bomb(Point center) :
		GameObject(new Circle(center, EXPLOSION_INITIAL_RADIUS)) {
	explosionCircle = (Circle*) shape;
	explosionTimer.start(0);
	finished = false;
}

int Bomb::update(double dt) {

	Vector2 vecDirection(1, 0);

	explosionCircle->setRadius(
			std::min(
					explosionCircle->getRadius()
							+ EXPLOSION_INCREASE_SPEED * dt,
					MAX_EXPLOSION_RADIUS));

	explosionTimer.update();
	if (explosionTimer.isDone()) {
		explosionTimer.start(EXPLOSION_TIME);

		for (float i = 0; i <= 359.0; i += EXPLOSION_DIFF_ANGLE) {
			Vector2 orientationToExplode = vecDirection.constantProduct(
					explosionCircle->getRadius()).rotateVector(i);
			int numSprites[1] = { 4 };
			AnimationManager::instantiate(
					explosionCircle->getCenterRef()->addVector(
							orientationToExplode),
					new Animation("../gfx/EnemyExplosion.png", 150, 1,
							numSprites, 77, false));
		}
	}

	if (explosionCircle->getRadius() >= MAX_EXPLOSION_RADIUS) {
		finished = true;
	}

	return 0;
}

void Bomb::render(float cameraX, float cameraY) {
}

void Bomb::onCollisionWithKillable(Killable* killable) {
	killable->attemptToKill(BOMB_DAMAGE);
}
