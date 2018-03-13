/*
 * PlayerGunMissile.h
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#ifndef PLAYERGUNMISSILE_H_
#define PLAYERGUNMISSILE_H_

#include "PlayerGun.h"

#define SHOT_SPEED_MISSILE 500
#define SHOT_COOLDOWN_MISSILE 400
#define GUN_MISSILE_DAMAGE 10

#define OUTER_SHOT_ANGLE 16
#define INNER_SHOT_ANGLE 10

#define ROTATE_SPEED_L1 20
#define ROTATE_SPEED_L2 25
#define ROTATE_SPEED_L3 35

class PlayerGunMissile: public PlayerGun {
private:
	Vector2 vecMiddleShotOffset;
	Vector2 vecShot1Offset;
	Vector2 vecShot2Offset;
	Vector2 vecShot3Offset;
	Vector2 vecShot4Offset;
public:
	PlayerGunMissile(int gunLevel, Sprite* bulletSprite,
			Point* shooterPositionRef = NULL);
	void shoot(Point position, Vector2 vecDirection, Point* targetPosition);
	void stopShooting();
	virtual ~PlayerGunMissile();
};

#endif /* PLAYERGUNMISSILE_H_ */
