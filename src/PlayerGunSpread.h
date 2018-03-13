/*
 * PlayerGunSpread.h
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#ifndef PLAYERGUNSPREAD_H_
#define PLAYERGUNSPREAD_H_

#define SHOT_COOLDOWN_SPREAD 150
#define SHOT_SPEED_SPREAD 500
#define GUN_BULLET_DAMAGE_LEVEL1 15
#define GUN_BULLET_DAMAGE_LEVEL2 10
#define GUN_BULLET_DAMAGE_LEVEL3 5

#define OUTER_SHOT_ANGLE 16
#define INNER_SHOT_ANGLE 10

#include "PlayerGun.h"
#include "Point.h"
#include "Vector2.h"
#include "Sprite.h"

class PlayerGunSpread: public PlayerGun {
private:
	bool circular;
	Vector2 vecShot1Offset;
	Vector2 vecShot2Offset;
	Vector2 vecShot3Offset;
	Vector2 vecShot4Offset;
	Vector2 vecShot5Offset;

public:
	PlayerGunSpread(int gunLevel = 1, Sprite* bulletSprite = NULL,
			bool circular = false, Point* shooterPositionRef = NULL);
	virtual ~PlayerGunSpread();

	void shoot(Point position, Vector2 vecDirection, Point* targetPosition);
	void stopShooting();
};

#endif /* PLAYERGUNSPREAD_H_ */
