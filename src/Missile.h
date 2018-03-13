/*
 * Missile.h
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#include "Bullet.h"
#include "Animation.h"
class Missile: public Bullet {
private:
	Point *targetPosition;
	Animation* missileAnimation;
	float rotateSpeed;

public:
	Missile(Vector2 velocity, bool isEnemy, Sprite* bulletSprite, Shape* shape,
			Point* targetPosition, float rotateSpeed, int damage);
	int update(double dt);
	void render(float cameraX,float cameraY);
	void explode();
	virtual ~Missile();
};

#endif /* MISSILE_H_ */
