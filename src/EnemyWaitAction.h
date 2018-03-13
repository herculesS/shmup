/*
 * EnemyWaitAction.h
 *
 *  Created on: 23/06/2013
 *      Author: Vitor
 */

#ifndef ENEMYWAITACTION_H_
#define ENEMYWAITACTION_H_

#include "Enemy.h"
#include "Timer.h"

class EnemyWaitAction: public EnemyAction {
private:
	Timer waitTimer;
	int waitTimeInMilliseconds;
	bool started;

public:
	EnemyWaitAction(int waitTimeInMilliseconds, Enemy* enemy);
	virtual ~EnemyWaitAction();

	void update(double dt);
};

#endif /* ENEMYWAITACTION_H_ */
