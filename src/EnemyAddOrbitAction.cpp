/*
 * EnemyAddOrbitAction.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Hercules
 */

#include "EnemyAddOrbitAction.h"

EnemyAddOrbitAction::EnemyAddOrbitAction(Enemy* orbit, Enemy* enemy) :
		EnemyAction(enemy) {
	orbitToAdd = orbit;
}

EnemyAddOrbitAction::~EnemyAddOrbitAction() {
	// TODO Auto-generated destructor stub
}

void EnemyAddOrbitAction::update(double dt) {
	this->enemy->addOrbit(this->orbitToAdd);
	this->enemy->setOrbitsCenterAsSelf();
	this->Done = true;
}

