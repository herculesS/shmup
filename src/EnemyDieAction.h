/*
 * EnemyDieAction.h
 *
 *  Created on: 29/06/2013
 *      Author: Vitor
 */

#ifndef ENEMYDIEACTION_H_
#define ENEMYDIEACTION_H_

#include "Enemy.h"

class EnemyDieAction: public EnemyAction {
public:
	EnemyDieAction(Enemy* enemy);
	virtual ~EnemyDieAction();

	void update(double dt);
};

#endif /* ENEMYDIEACTION_H_ */
