/*
 * BulletPatternSpread.cpp
 *
 *  Created on: 05/05/2013
 *      Author: Vitor
 */

#include "BulletPatternSpread.h"

BulletPatternSpread::BulletPatternSpread(int numShots, float shotVelocity,
		int waitInMillisecondsBetweenShots, float arcInDegrees, int numRepeats,
		Sprite* bulletSprite, bool circular) :
		BulletPattern(bulletSprite, circular) {
	this->numShots = std::max(0, numShots);
	this->shotVelocity = shotVelocity;
	this->waitInMillisecondsBetweenShots = std::max(0,
			waitInMillisecondsBetweenShots);
	this->arcInDegrees = std::max((float) 0, arcInDegrees);
	this->numRepeats = std::max(0, numRepeats);

	timerBetweenShots.start(0);
}

BulletPatternSpread::~BulletPatternSpread() {
	// TODO Auto-generated destructor stub
}

void BulletPatternSpread::shoot(Point shooterPosition, Point toShoot) {

	Vector2 vecDirection(1, 0);

	if (numRepeats > 0) {
		timerBetweenShots.update();
		if (timerBetweenShots.isDone()) {
			timerBetweenShots.start(waitInMillisecondsBetweenShots);

			Vector2 enemyToPlayer = toShoot.createVector(shooterPosition);
			enemyToPlayer = enemyToPlayer.normalize();

			// Se for só um tiro, atire direto no Player
			if (numShots == 1) {
				BulletManager::instantiate(shooterPosition,
						enemyToPlayer.constantProduct(shotVelocity), true,
						bulletSprite, circular);
			} else {

				float arcIncrementInDegrees = arcInDegrees / (numShots - 1);
				float angleToPlayerInDegrees = atan2(enemyToPlayer.getY(),
						enemyToPlayer.getX()) * 180 / M_PI;

				float arcStartInDegrees = angleToPlayerInDegrees
						- (arcInDegrees / 2);
				// O fim é dado por arcEndInDegrees + 1 para dar uma tolerância
				// de 1 grau para a instaciação dos tiros
				float arcEndInDegrees = angleToPlayerInDegrees
						+ (arcInDegrees / 2) + 1;
				float currentArc;

				for (currentArc = arcStartInDegrees;
						currentArc < arcEndInDegrees; currentArc +=
								arcIncrementInDegrees) {
					BulletManager::instantiate(shooterPosition,
							vecDirection.rotateVector(currentArc).constantProduct(
									shotVelocity), true, bulletSprite,
							circular);
				}

			}

			numRepeats--;

		}
	}
}
