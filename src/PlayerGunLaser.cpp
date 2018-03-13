/*
 * PlayerGunLaser.cpp
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#include "PlayerGunLaser.h"

PlayerGunLaser::PlayerGunLaser(std::vector<Sprite*> bulletSprites, int gunLevel,
		Sprite* levelOneBulletSprite, Point* shooterPositionRef) :
		PlayerGun(gunLevel, levelOneBulletSprite, shooterPositionRef) {
	Vector2 vecDirection(0, -1);

	vecMiddleShotOffset = vecDirection.constantProduct(CENTER_DISTANCE);
	vecShot1Offset = vecDirection.rotateVector(OUTER_ANGLE).constantProduct(
			OUTER_DISTANCE);
	vecShot2Offset = vecDirection.rotateVector(INNER_ANGLE).constantProduct(
			INNER_DISTANCE);
	vecShot3Offset = vecDirection.rotateVector(-INNER_ANGLE).constantProduct(
			INNER_DISTANCE);
	vecShot4Offset = vecDirection.rotateVector(-OUTER_ANGLE).constantProduct(
			OUTER_DISTANCE);

	this->bulletSprites = bulletSprites;

	shotCooldown.start(0);
}

PlayerGunLaser::~PlayerGunLaser() {
}

void PlayerGunLaser::shoot(Point position, Vector2 vecDirection,
		Point* targetPosition) {

	shotCooldown.update();

	if (shotCooldown.isDone()) {
		shotCooldown.start(SHOT_COOLDOWN_LASER);
		switch (gunLevel) {
		case 1:
			bulletSprite = bulletSprites[0];
			BulletManager::instantiateLaser(
					position.addVector(vecMiddleShotOffset),
					vecDirection.constantProduct(SHOT_SPEED_LASER), false,
					bulletSprite, shooterPositionRef,
					GUN_LASER_BULLET_DAMAGE_LEVEL1);
			break;
		case 2:
			bulletSprite = bulletSprites[1];
			BulletManager::instantiateLaser(
					position.addVector(vecMiddleShotOffset),
					vecDirection.constantProduct(SHOT_SPEED_LASER), false,
					bulletSprite, shooterPositionRef,
					GUN_LASER_BULLET_DAMAGE_LEVEL2);
			break;
		default:
			bulletSprite = bulletSprites[2];
			BulletManager::instantiateLaser(
					position.addVector(vecMiddleShotOffset),
					vecDirection.constantProduct(SHOT_SPEED_LASER), false,
					bulletSprite, shooterPositionRef,
					GUN_LASER_BULLET_DAMAGE_LEVEL3);
			break;
		}
	}

}

void PlayerGunLaser::stopShooting() {
	BulletManager::removeAllPlayerBullets();
}
