/*
 * BulletPatternSpread.h
 *
 *  Created on: 05/05/2013
 *      Author: Vitor
 */

#ifndef BULLETPATTERNSPREAD_H_
#define BULLETPATTERNSPREAD_H_

#include "BulletPattern.h"
#include "BulletManager.h"
#include "Point.h"
#include "Timer.h"
#include "Vector2.h"
#include <math.h>

class BulletPatternSpread: public BulletPattern {
private:
	int numShots;
	float shotVelocity;
	int waitInMillisecondsBetweenShots;
	float arcInDegrees;
	int numRepeats;
	Timer timerBetweenShots;

public:
	BulletPatternSpread(int numShots, float shotVelocity,
			int waitInMillisecondsBetweenShots, float arcInDegrees,
			int numRepeats, Sprite* bulletSprite, bool circular);
	virtual ~BulletPatternSpread();
	void shoot(Point shooterPosition, Point toShoot = Point(0, 0));
};

#endif /* BULLETPATTERNSPREAD_H_ */
