/*
 * LaserBullet.h
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#ifndef LASERBULLET_H_
#define LASERBULLET_H_

#include "Bullet.h"
#include "Point.h"
#include "Vector2.h"
#include "Sprite.h"

class LaserBullet: public Bullet {
private:
	Point* shooterPositionRef;
	int xOffset; // Esse offset � equivalente a (pos. x de onde tiro deve estar - pos. x do shooter)

public:
	LaserBullet(Vector2 vecSpeed, bool isEnemy, Sprite* bulletSprite,
			Point* shooterPositionRef, Shape* shape, int damage);
	virtual ~LaserBullet();
	void explode();
	int update(double dt);
};

#endif /* LASERBULLET_H_ */
