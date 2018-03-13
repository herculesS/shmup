/*
 * Missile.cpp
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#include "Missile.h"

Missile::Missile(Vector2 velocity, bool isEnemy, Sprite* bulletSprite,
		Shape* shape, Point *targetPosition, float rotateSpeed, int damage) :
		Bullet(velocity, isEnemy, bulletSprite, shape, damage) {
	this->targetPosition = targetPosition;
	this->rotateSpeed = rotateSpeed;
	int numberOfSpritesInEachRow[1] = { 4 };
	missileAnimation = new Animation("../gfx/missileAnimation.png", 10, 1,
			numberOfSpritesInEachRow, 27, true);
}
int Missile::update(double dt) {
	Vector2 vetToTarget(targetPosition->getX() - shape->getCenterRef()->getX(),
			targetPosition->getY() - shape->getCenterRef()->getY());

	// Essa posi��o (400, -600) foi convencionada ser a posi��o de "n�o h� alvo, siga reto"
	if (targetPosition->getX() != 400 || targetPosition->getY() != -600) {
		vetToTarget = vetToTarget.normalize().constantProduct(rotateSpeed);
		Vector2 addedVec = vetToTarget.add(this->velocity);
		velocity = addedVec.normalize().constantProduct(velocity.length());
	}

	Bullet::update(dt);
	missileAnimation->update(dt);
	return 0;
}
void Missile::explode() {
	int numOfSprites[1] = { 4 };
	AnimationManager::instantiate(
			shape->getCenterRef()->addVector(velocity.constantProduct(.03)),
			new Animation("../gfx/MissileExplosion.png", 100, 1, numOfSprites,
					26, false));
	onHitSound = new Sound("../sfx/missile.wav");
	onHitSound->play(1);
	onHitSound->setVolume(10);
}
void Missile::render(float cameraX, float cameraY) {
	this->missileAnimation->rotoZoom(
			atan2(-velocity.getY(), velocity.getX()) * 180 / M_PI, 1, 1, false);
	missileAnimation->render(shape->getCenterRef()->getX() - cameraX,
			shape->getCenterRef()->getY() - cameraY, true,
			GameArea::getSurface());
}
Missile::~Missile() {
	// TODO Auto-generated destructor stub
	delete (missileAnimation);
}

