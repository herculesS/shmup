/*
 * PlayerGunMissile.cpp
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#include "PlayerGunMissile.h"

PlayerGunMissile::PlayerGunMissile(int gunLevel, Sprite* bulletSprite,
		Point* shooterPositionRef) :
		PlayerGun(gunLevel, bulletSprite, shooterPositionRef) {
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

	shotCooldown.start(0);

}

void PlayerGunMissile::stopShooting() {

}

void PlayerGunMissile::shoot(Point position, Vector2 vecDirection,
		Point* targetPosition) {
	shotCooldown.update();
	if (shotCooldown.isDone()) {
		shotCooldown.start(SHOT_COOLDOWN_MISSILE);
		switch (gunLevel) {
		case 1:
			BulletManager::instantiateMissile(
					position.addVector(vecMiddleShotOffset),
					vecDirection.constantProduct(SHOT_SPEED_MISSILE), false,
					bulletSprite, targetPosition, ROTATE_SPEED_L1,
					GUN_MISSILE_DAMAGE);
			break;
		case 2:
			BulletManager::instantiateMissile(
					position.addVector(vecShot2Offset),
					vecDirection.rotateVector(INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L2, GUN_MISSILE_DAMAGE);
			BulletManager::instantiateMissile(
					position.addVector(vecShot3Offset),
					vecDirection.rotateVector(-INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L2, GUN_MISSILE_DAMAGE);
			break;

		default:
			BulletManager::instantiateMissile(
					position.addVector(vecMiddleShotOffset),
					vecDirection.constantProduct(SHOT_SPEED_MISSILE), false,
					bulletSprite, targetPosition, ROTATE_SPEED_L3,
					GUN_MISSILE_DAMAGE);
			BulletManager::instantiateMissile(
					position.addVector(vecShot1Offset),
					vecDirection.rotateVector(OUTER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L3, GUN_MISSILE_DAMAGE);
			BulletManager::instantiateMissile(
					position.addVector(vecShot2Offset),
					vecDirection.rotateVector(INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L3, GUN_MISSILE_DAMAGE);
			BulletManager::instantiateMissile(
					position.addVector(vecShot3Offset),
					vecDirection.rotateVector(-INNER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L3, GUN_MISSILE_DAMAGE);
			BulletManager::instantiateMissile(
					position.addVector(vecShot4Offset),
					vecDirection.rotateVector(-OUTER_SHOT_ANGLE).constantProduct(
							SHOT_SPEED_MISSILE), false, bulletSprite,
					targetPosition, ROTATE_SPEED_L3, GUN_MISSILE_DAMAGE);
		}
	}
}

PlayerGunMissile::~PlayerGunMissile() {
	// TODO Auto-generated destructor stub
}

