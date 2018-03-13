/*
 * PlayerGunLaser.h
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#ifndef PLAYERGUNLASER_H_
#define PLAYERGUNLASER_H_

#define SHOT_COOLDOWN_LASER 10
#define SHOT_SPEED_LASER 800
#define GUN_LASER_BULLET_DAMAGE_LEVEL1 1
#define GUN_LASER_BULLET_DAMAGE_LEVEL2 3
#define GUN_LASER_BULLET_DAMAGE_LEVEL3 5

#include "PlayerGun.h"
#include "Vector2.h"
#include "Point.h"
#include "Sprite.h"

class PlayerGunLaser: public PlayerGun {
private:
	Vector2 vecMiddleShotOffset; // Usado apenas no tiro de n�vel 1
	Vector2 vecShot1Offset;
	Vector2 vecShot2Offset;
	Vector2 vecShot3Offset;
	Vector2 vecShot4Offset;

	// Posicao 0: sprite laser level 1
	// Posicao 1: sprite laser level 2
	// etc.
	std::vector<Sprite*> bulletSprites;

public:
	PlayerGunLaser(std::vector<Sprite*> bulletSprites, int gunLevel = 1,
			Sprite* levelOnebulletSprite = NULL, Point* shooterPositionRef =
					NULL);
	virtual ~PlayerGunLaser();

	void shoot(Point position, Vector2 vecDirection, Point* targetPosition);
	void stopShooting();
};

#endif /* PLAYERGUNLASER_H_ */
