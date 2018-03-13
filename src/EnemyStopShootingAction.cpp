/*
 * EnemyStopShootingAction.cpp
 *
 *  Created on: 27/06/2013
 *      Author: Vitor
 */

#include "EnemyStopShootingAction.h"

EnemyStopShootingAction::EnemyStopShootingAction(Enemy* enemy) :
		EnemyAction(enemy) {
}

EnemyStopShootingAction::~EnemyStopShootingAction() {
	// TODO Auto-generated destructor stub
}

void EnemyStopShootingAction::update(double dt) {
	enemy->setShooting(false);
	this->Done = true;
}
