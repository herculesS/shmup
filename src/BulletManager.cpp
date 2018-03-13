/*
 * BulletManager.cpp
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#include "BulletManager.h"

std::vector<Bullet*> BulletManager::enemyBulletList;
std::vector<Bullet*> BulletManager::playerBulletList;

void BulletManager::instantiate(Point position, Vector2 velocity, bool isEnemy,
		Sprite* bulletSprite, bool circular, int damage) {
	Bullet* newBullet;
	Shape* bulletShape;

	float rotationAngleInDegrees = atan2(-velocity.getY(), velocity.getX())
			* 180 / M_PI;

	if (circular) {
		bulletShape = new Circle(position,
				(bulletSprite->getWidth() * 0.8) / 2);
	} else {
		bulletShape = new Rect(position, bulletSprite->getWidth() * 0.8,
				bulletSprite->getHeight() * 0.8, rotationAngleInDegrees);
	}

	newBullet = new Bullet(velocity, isEnemy, bulletSprite, bulletShape,
			damage);

	isEnemy ?
			enemyBulletList.push_back(newBullet) :
			playerBulletList.push_back(newBullet);

}

void BulletManager::instantiateLaser(Point position, Vector2 velocity,
		bool enemyBullet, Sprite* bulletSprite, Point* shooterPositionRef,
		int damage) {
	LaserBullet* newBullet;

	newBullet = new LaserBullet(velocity, enemyBullet, bulletSprite,
			shooterPositionRef,
			new Rect(position, bulletSprite->getWidth(),
					bulletSprite->getHeight()), damage);

	enemyBullet ?
			enemyBulletList.push_back(newBullet) :
			playerBulletList.push_back(newBullet);
}

void BulletManager::instantiateMissile(Point position, Vector2 velocity,
		bool enemyBullet, Sprite* bulletSprite, Point* targetPositionRef,
		float rotateSpeed, int damage) {
	Missile* newBullet;
	if (targetPositionRef != NULL) {

		newBullet = new Missile(velocity, enemyBullet, bulletSprite,
				new Rect(position, bulletSprite->getWidth(),
						bulletSprite->getHeight()), targetPositionRef,
				rotateSpeed, damage);

		enemyBullet ?
				enemyBulletList.push_back(newBullet) :
				playerBulletList.push_back(newBullet);
	}
}
void BulletManager::update(double dt) {
	for (std::vector<Bullet*>::iterator it = enemyBulletList.begin();
			it != enemyBulletList.end(); it++) {
		(*it)->update(dt);
		if ((*it)->isDead()) {
			delete (*it);
			it = enemyBulletList.erase(it);
			it--;
		}
	}

	for (std::vector<Bullet*>::iterator it = playerBulletList.begin();
			it != playerBulletList.end(); it++) {
		(*it)->update(dt);
		if ((*it)->isDead()) {
			delete (*it);
			it = playerBulletList.erase(it);
			it--;
		}
	}
}

void BulletManager::render(float cameraX, float cameraY) {
	for (std::vector<Bullet*>::iterator it = playerBulletList.begin();
			it != playerBulletList.end(); it++) {
		(*it)->render(cameraX, cameraY);
	}
	for (std::vector<Bullet*>::iterator it = enemyBulletList.begin();
			it != enemyBulletList.end(); it++) {
		(*it)->render(cameraX, cameraY);
	}
}

Bullet* BulletManager::checkCollision(GameObject* target, bool targetIsEnemy) {

	std::vector<Bullet*> vectorToCheck;

	targetIsEnemy ? vectorToCheck = playerBulletList : vectorToCheck =
							enemyBulletList;

	for (std::vector<Bullet*>::iterator it = vectorToCheck.begin();
			it != vectorToCheck.end(); it++) {
		if (CollisionManager::checkCollision(target->getShape(),
				(*it)->getShape()))
			return *it;
	}

	return NULL;
}

std::vector<Bullet*> BulletManager::checkCollisions(GameObject* target,
		bool targetIsEnemy) {
	std::vector<Bullet*> vectorToCheck;
	std::vector<Bullet*> toReturn;

	targetIsEnemy ? vectorToCheck = playerBulletList : vectorToCheck =
							enemyBulletList;

	for (std::vector<Bullet*>::iterator it = vectorToCheck.begin();
			it != vectorToCheck.end(); it++) {
		if (CollisionManager::checkCollision(target->getShape(),
				(*it)->getShape())) {
			toReturn.push_back((*it));
		}
	}

	return toReturn;
}

void BulletManager::cleanUp() {

	for (std::vector<Bullet*>::iterator it = enemyBulletList.begin();
			it != enemyBulletList.end(); it++) {
		it = enemyBulletList.erase(it);
		it--;
	}

	for (std::vector<Bullet*>::iterator it = playerBulletList.begin();
			it != playerBulletList.end(); it++) {
		it = playerBulletList.erase(it);
		it--;
	}

}

// Nessa fun��o presume-se que os par�metros passados sejam da tela
// Ent�o a posi��o da �rea � fixada como (0, 0)
void BulletManager::removeOffScreenBullets(float areaWidth, float areaHeight) {

	for (std::vector<Bullet*>::iterator it = enemyBulletList.begin();
			it != enemyBulletList.end(); it++) {
		if (!valueInRange((*it)->getShape()->getX(), 0, areaWidth)
				|| !valueInRange((*it)->getShape()->getY(), 0, areaHeight)) {
			(*it)->setDead(true);
		}
	}

	for (std::vector<Bullet*>::iterator it = playerBulletList.begin();
			it != playerBulletList.end(); it++) {
		if (!valueInRange((*it)->getShape()->getX(), 0, areaWidth)
				|| !valueInRange((*it)->getShape()->getY(), 0, areaHeight)) {
			(*it)->setDead(true);
		}
	}
}

void BulletManager::removeAllPlayerBullets() {
	for (std::vector<Bullet*>::iterator it = playerBulletList.begin();
			it != playerBulletList.end(); it++) {
		(*it)->setDead(true);
	}
}

bool BulletManager::valueInRange(float value, float min, float max) {
	return (value >= min) && (value <= max);
}
