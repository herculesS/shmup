/*
 * EnemyShootAction.h
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#ifndef ENEMYSHOOTACTION_H_
#define ENEMYSHOOTACTION_H_

#include "Enemy.h"
#include "BulletManager.h"
#include "Timer.h"

class EnemyShootAction: public EnemyAction {
public:
	EnemyShootAction(Enemy *enemy);
	void update(double dt);
	virtual ~EnemyShootAction();
};

#endif /* ENEMYSHOOTACTION_H_ */
