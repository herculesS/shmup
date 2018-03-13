/*
 * BulletPattern.h
 *
 *  Created on: 27/04/2013
 *      Author: Vitor
 */

#ifndef BULLETPATTERN_H_
#define BULLETPATTERN_H_

#include "Point.h"
#include "Sprite.h"
#include "Shape.h"

class BulletPattern {
protected:
	Sprite* bulletSprite;
	bool circular;

public:
	BulletPattern(Sprite* bulletSprite, bool circular);
	virtual ~BulletPattern();
	virtual void shoot(Point shooterPosition, Point toShoot = Point(0, 0)) = 0;
};

#endif /* BULLETPATTERN_H_ */
