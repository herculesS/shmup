/*
 * EnemyStopShootingAction.h
 *
 *  Created on: 27/06/2013
 *      Author: Vitor
 */

#ifndef ENEMYSTOPSHOOTINGACTION_H_
#define ENEMYSTOPSHOOTINGACTION_H_

#include "Enemy.h"

class EnemyStopShootingAction: public EnemyAction {
public:
	EnemyStopShootingAction(Enemy* enemy);
	void update(double dt);
	virtual ~EnemyStopShootingAction();
};

#endif /* ENEMYSTOPSHOOTINGACTION_H_ */
