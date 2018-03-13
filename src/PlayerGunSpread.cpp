/*
 * PlayerGunSpread.cpp
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#include "PlayerGunSpread.h"

PlayerGunSpread::PlayerGunSpread(int gunLevel, Sprite* bulletSprite,
		bool circular, Point* shooterPositionRef) :
		PlayerGun(gunLevel, bulletSprite, shooterPositionRef) {
	Vector2 vecDirection(0, -1);

	vecShot1Offset = vecDirection.rotateVector(OUTER_ANGLE).constantProduct(
			OUTER_DISTANCE);
	vecShot2Offset = vecDirection.rotateVector(INNER_ANGLE).constantProduct(
			INNER_DISTANCE);
	vecShot3Offset = vecDirection.constantProduct(CENTER_DISTANCE);
	vecShot4Offset = vecDirection.rotateVector(-INNER_ANGLE).constantProduct(
			INNER_DISTANCE);
	vecShot5Offset = vecDirection.rotateVector(-OUTER_ANGLE).constantProduct(
			OUTER_DISTANCE);

	this->circular = circular;

	shotCooldown.start(0);
}

PlayerGunSpread::~PlayerGunSpread() {
}

void PlayerGunSpread::shoot(Point position, Vector2 vecDirection,
		Point* targetPosition) {

	shotCooldown.update();

	if (shotCooldown.isDone()) {
		shotCooldown.start(SHOT_COOLDOWN_SPREAD);
		switch (gunLevel) {
		case 1:
			BulletManager::instantiate(position.addVector(vecShot3Offset),
					vecDirection.constantProduct(SHOT_SPEED_SPREAD), false,
					bulletSprite, circular, GUN_BULLET_DAMAGE_LEVEL1);
			break;
		case 2:
			BulletManager::instantiate(position.addVector(vecShot2Offset),
					vecDirection.rotateVector(INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL2);
			BulletManager::instantiate(position.addVector(vecShot3Offset),
					vecDirection.constantProduct(SHOT_SPEED_SPREAD), false,
					bulletSprite, circular, GUN_BULLET_DAMAGE_LEVEL2);
			BulletManager::instantiate(position.addVector(vecShot4Offset),
					vecDirection.rotateVector(-INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL2);
			break;
		default:
			BulletManager::instantiate(position.addVector(vecShot1Offset),
					vecDirection.rotateVector(OUTER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL3);
			BulletManager::instantiate(position.addVector(vecShot2Offset),
					vecDirection.rotateVector(INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL3);
			BulletManager::instantiate(position.addVector(vecShot3Offset),
					vecDirection.constantProduct(SHOT_SPEED_SPREAD), false,
					bulletSprite, circular, GUN_BULLET_DAMAGE_LEVEL3);
			BulletManager::instantiate(position.addVector(vecShot4Offset),
					vecDirection.rotateVector(-INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL3);
			BulletManager::instantiate(position.addVector(vecShot5Offset),
					vecDirection.rotateVector(-OUTER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_SPREAD), false, bulletSprite, circular,
					GUN_BULLET_DAMAGE_LEVEL3);
			break;
		}
	}
}

void PlayerGunSpread::stopShooting() {
}
