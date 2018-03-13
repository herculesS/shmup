/*
 * EnemyAddPatternAction.h
 *
 *  Created on: 29/06/2013
 *      Author: Vitor
 */

#ifndef ENEMYADDPATTERNACTION_H_
#define ENEMYADDPATTERNACTION_H_

#include "Enemy.h"

class EnemyAddPatternAction: public EnemyAction {
private:
	BulletPattern* patternToAdd;

public:
	EnemyAddPatternAction(BulletPattern* patternToAdd, Enemy* enemy);
	virtual ~EnemyAddPatternAction();

	void update(double dt);
};

#endif /* ENEMYADDPATTERNACTION_H_ */
