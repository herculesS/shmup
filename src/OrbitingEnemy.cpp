/*
 * OrbitingEnemy.cpp
 *
 *  Created on: 28/06/2013
 *      Author: Vitor
 */

#include "OrbitingEnemy.h"

OrbitingEnemy::OrbitingEnemy(Sprite* sprite, GameObject* target, Shape* shape,
		int life, Animation* hitAnimation, Enemy* orbitCenter,
		float initialAngle, float angularSpeed, float radius, bool clockwise) :
		Enemy(sprite, target, shape, life, 0, hitAnimation) {
	this->initialAngle = initialAngle;
	this->clockwise = clockwise;
	this->angularSpeed = angularSpeed * (clockwise ? 1 : -1);
	this->radius = radius;
	this->currentRotation = 0;
	this->orbitCenter = orbitCenter;
	this->scorePoints = 10;
}

OrbitingEnemy::OrbitingEnemy(Enemy* enemy, Enemy* orbitCenter,
		float initialAngle, float angularSpeed, float radius, bool clockwise) :
		Enemy(*enemy) {
	this->initialAngle = initialAngle;
	this->clockwise = clockwise;
	this->angularSpeed = angularSpeed * (clockwise ? 1 : -1);
	this->radius = radius;
	this->currentRotation = 0;
	this->orbitCenter = orbitCenter;
	//this->scorePoints = 10;
}

OrbitingEnemy::~OrbitingEnemy() {
	// TODO Auto-generated destructor stub
}

int OrbitingEnemy::update(double dt) {

	Vector2 vecDirection(1, 0);
	Vector2 actualPosition;

	Enemy::update(dt);

	actualPosition =
			vecDirection.rotateVector(initialAngle + currentRotation).constantProduct(
					radius);

	shape->setCenter(
			Point(orbitCenter->getShape()->getX() + actualPosition.getX(),
					orbitCenter->getShape()->getY() + actualPosition.getY()));

	currentRotation += angularSpeed * dt;

	if (!dead)
		this->setDead(orbitCenter->isDead());

	return 0;
}

void OrbitingEnemy::explode() {
	AnimationManager::instantiate(*this->getShape()->getCenterRef(),
			this->onDeathExplosion.at(1));

}
