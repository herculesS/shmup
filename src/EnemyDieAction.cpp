/*
 * EnemyDieAction.cpp
 *
 *  Created on: 29/06/2013
 *      Author: Vitor
 */

#include "EnemyDieAction.h"

EnemyDieAction::EnemyDieAction(Enemy* enemy) :
		EnemyAction(enemy) {
}

EnemyDieAction::~EnemyDieAction() {
	// TODO Auto-generated destructor stub
}

void EnemyDieAction::update(double dt) {
	enemy->setDead(true);
	enemy->setKilled(false);
	enemy->setScorePoints(0);
	enemy->clearDrops();
	this->Done = true;
}
