/*
 * BulletPatternBurst.cpp
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#include "BulletPatternBurst.h"

BulletPatternBurst::BulletPatternBurst(int numShots, float shotVelocity,
		int waitInMilliseconds, int numRepeats, Sprite* bulletSprite,
		bool circular) :
		BulletPattern(bulletSprite, circular) {
	this->numShots = std::max(0, numShots);
	this->shotVelocity = shotVelocity;
	this->waitInMillisecondsBetweenShots = waitInMilliseconds;
	this->numRepeats = std::max(0, numRepeats);

	timerBetweenShots.start(0);
}

BulletPatternBurst::~BulletPatternBurst() {
	// TODO Auto-generated destructor stub
}

void BulletPatternBurst::shoot(Point shooterPosition, Point toShoot) {

	Vector2 vecDirection(1, 0);

	if (numRepeats > 0) {
		timerBetweenShots.update();
		if (timerBetweenShots.isDone()) {

			timerBetweenShots.start(waitInMillisecondsBetweenShots);

			float rotationInDegrees = 0;
			float angleIncrement = 360.0 / numShots;

			for (int i = 0; i < numShots; i++) {
				BulletManager::instantiate(shooterPosition,
						vecDirection.rotateVector(rotationInDegrees).constantProduct(
								shotVelocity), true, bulletSprite, circular);
				rotationInDegrees += angleIncrement;
			}

			numRepeats--;

		}
	}
}
