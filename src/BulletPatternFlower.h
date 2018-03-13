/*
 * BulletPatternFlower.h
 *
 *  Created on: 03/05/2013
 *      Author: Vitor
 */

#ifndef BULLETPATTERNFLOWER_H_
#define BULLETPATTERNFLOWER_H_

#include "BulletPattern.h"
#include "BulletManager.h"
#include "Point.h"
#include "Timer.h"
#include "Vector2.h"
#include <math.h>

class BulletPatternFlower: public BulletPattern {
private:
	int numShots;
	float shotVelocity;
	int waitInMillisecondsBetweenShots;
	float angleBetweenBulletsInDegrees;
	int numRepeats;
	float currentRotation;
	bool clockwise;
	Timer timerBetweenShots;

public:
	BulletPatternFlower(int numShots, float shotVelocity,
			int waitInMillisecondsBetweenShots,
			float angleBetweenBulletsInDegrees, int numRepeats, bool clockwise,
			Sprite* bulletSprite, bool circular);
	virtual ~BulletPatternFlower();
	void shoot(Point shooterPosition, Point toShoot = Point(0, 0));
};

#endif /* BULLETPATTERNFLOWER_H_ */
