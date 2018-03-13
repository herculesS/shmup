/*
 * PlayerGun.h
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#ifndef PLAYERGUN_H_
#define PLAYERGUN_H_

#define OUTER_ANGLE 100
#define INNER_ANGLE 90
#define OUTER_DISTANCE 20
#define INNER_DISTANCE 10
#define CENTER_DISTANCE 10

#include "Timer.h"
#include "BulletManager.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector2.h"

class PlayerGun {
protected:
	Sprite* bulletSprite;
	int gunLevel;
	Timer shotCooldown;
	Point* shooterPositionRef;

public:
	PlayerGun(int gunLevel, Sprite* bulletSprite, Point* shooterPositionRef =
			NULL);
	virtual ~PlayerGun();

	virtual void shoot(Point position, Vector2 vecDirection,
			Point* targetPosition) = 0;
	virtual void stopShooting() = 0;

	int getGunLevel() const {
		return gunLevel;
	}

	void setGunLevel(int gunLevel) {
		this->gunLevel = gunLevel;
	}

	void setBulletSprite(Sprite* bulletSprite) {
		this->bulletSprite = bulletSprite;
	}

	void setShooterPositionRef(Point* shooterPositionRef) {
		this->shooterPositionRef = shooterPositionRef;
	}
};

#endif /* PLAYERGUN_H_ */
