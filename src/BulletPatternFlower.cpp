/*
 * BulletPatternFlower.cpp
 *
 *  Created on: 03/05/2013
 *      Author: Vitor
 */

#include "BulletPatternFlower.h"

BulletPatternFlower::BulletPatternFlower(int numShots, float shotVelocity,
		int waitInMillisecondsBetweenShots, float angleBetweenBulletsInDegrees,
		int numRepeats, bool clockwise, Sprite* bulletSprite, bool circular) :
		BulletPattern(bulletSprite, circular) {
	this->numShots = std::max(0, numShots);
	this->shotVelocity = shotVelocity;
	this->waitInMillisecondsBetweenShots = waitInMillisecondsBetweenShots;
	this->clockwise = clockwise;
	this->angleBetweenBulletsInDegrees = (angleBetweenBulletsInDegrees
			* (clockwise ? 1 : -1));
	this->numRepeats = std::max(0, numRepeats);
	this->currentRotation = 0;

	timerBetweenShots.start(0);
}

BulletPatternFlower::~BulletPatternFlower() {
	// TODO Auto-generated destructor stub
}

void BulletPatternFlower::shoot(Point shooterPosition, Point toShoot) {

	Vector2 vecDirection(1, 0);

	if (this->numRepeats > 0) {
		timerBetweenShots.update();
		if (timerBetweenShots.isDone()) {

			timerBetweenShots.start(waitInMillisecondsBetweenShots);

			float degreesBetweenShots = 360.0 / this->numShots;
			float rotationBetweenShots = 0;

			for (int i = 0; i < this->numShots; i++) {
				BulletManager::instantiate(shooterPosition,
						vecDirection.rotateVector(
								rotationBetweenShots + currentRotation).constantProduct(
								this->shotVelocity), true, bulletSprite,
						circular);
				rotationBetweenShots += degreesBetweenShots;
			}

			this->currentRotation += this->angleBetweenBulletsInDegrees;

			if (fabs(this->currentRotation) > 360) {
				this->currentRotation += clockwise ? -(360) : 360;
				this->numRepeats--;
			}

		}
	}

}
