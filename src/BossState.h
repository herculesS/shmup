/*
 * BossState.h
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#ifndef BOSSSTATE_H_
#define BOSSSTATE_H_

#include "Enemy.h"
class BossState {
private:
	Enemy *toCopy;
	float lifeBarScale;
	Sprite* lifeBarSprite;
	int duration;
public:
	BossState(Enemy *toCopy, Sprite* lifeBarSprite, int duration);
	Enemy* getEnemyToCopy();
	int getDuration();
	float getLifeBarScale();
	Sprite* getLifeBarSprite();
	virtual ~BossState();
};

#endif /* BOSSSTATE_H_ */
