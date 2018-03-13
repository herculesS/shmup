/*
 * LaserBullet.cpp
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#include "LaserBullet.h"

LaserBullet::LaserBullet(Vector2 vecSpeed, bool isEnemy, Sprite* bulletSprite,
		Point* shooterPositionRef, Shape* shape, int damage) :
		Bullet(vecSpeed, isEnemy, bulletSprite, shape, damage) {
	this->shooterPositionRef = shooterPositionRef;
	this->xOffset = shape->getX() - shooterPositionRef->getX();
}

LaserBullet::~LaserBullet() {
	// TODO Auto-generated destructor stub
}
void LaserBullet::explode() {
	int numOfSprites[1] = { 4 };
	Point temp(*shape->getCenterRef());
	temp.setY(temp.getY());
	AnimationManager::instantiate(temp,
			new Animation("../gfx/LaserExplosion.png", 50, 1, numOfSprites, 38,
					false));

}
int LaserBullet::update(double dt) {
	Bullet::update(dt);
	shape->setX(shooterPositionRef->getX() + xOffset);
	return 0;
}
