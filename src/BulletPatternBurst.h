/*
 * BulletPatternBurst.h
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#ifndef BULLETPATTERNBURST_H_
#define BULLETPATTERNBURST_H_

#include "BulletPattern.h"
#include "BulletManager.h"
#include "Point.h"
#include "Timer.h"
#include "Vector2.h"
#include <math.h>

class BulletPatternBurst: public BulletPattern {
private:
	int numShots;
	float shotVelocity;
	int waitInMillisecondsBetweenShots;
	int numRepeats;
	Timer timerBetweenShots;

public:
	BulletPatternBurst(int numShots, float shotVelocity, int waitInMilliseconds,
			int numRepeats, Sprite* bulletSprite, bool circular);
	virtual ~BulletPatternBurst();
	void shoot(Point shooterPosition, Point toShoot = Point(0, 0));
};

#endif /* BULLETPATTERNBURST_H_ */
