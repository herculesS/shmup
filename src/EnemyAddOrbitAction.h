/*
 * EnemyAddOrbitAction.h
 *
 *  Created on: Jul 21, 2013
 *      Author: Hercules
 */

#ifndef ENEMYADDORBITACTION_H_
#define ENEMYADDORBITACTION_H_

#include "Enemy.h"

class EnemyAddOrbitAction: public EnemyAction {
private:
	Enemy* orbitToAdd;

public:
	EnemyAddOrbitAction(Enemy* orbit, Enemy* enemy);
	void update(double dt);
	virtual ~EnemyAddOrbitAction();
};

#endif /* ENEMYADDORBITACTION_H_ */
