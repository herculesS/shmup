/*
 * EnemyAction.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#include "Enemy.h"

EnemyAction::EnemyAction(Enemy* enemy) {
	this->enemy = enemy;
	this->Done = false;
}

EnemyAction::~EnemyAction() {
	// TODO Auto-generated destructor stub
}

