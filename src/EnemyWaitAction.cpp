/*
 * EnemyWaitAction.cpp
 *
 *  Created on: 23/06/2013
 *      Author: Vitor
 */

#include "EnemyWaitAction.h"

EnemyWaitAction::EnemyWaitAction(int waitTimeInMilliseconds, Enemy* enemy) :
		EnemyAction(enemy) {
	started = false;
	this->waitTimeInMilliseconds = waitTimeInMilliseconds;
}

EnemyWaitAction::~EnemyWaitAction() {
	// TODO Auto-generated destructor stub
}

void EnemyWaitAction::update(double dt) {

	if (!started) {
		waitTimer.start(waitTimeInMilliseconds);
		started = true;
	}

	waitTimer.update();

	this->Done = waitTimer.isDone();
}
