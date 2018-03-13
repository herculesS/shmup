/*
 * EnemyAddPatternAction.cpp
 *
 *  Created on: 29/06/2013
 *      Author: Vitor
 */

#include "EnemyAddPatternAction.h"

EnemyAddPatternAction::EnemyAddPatternAction(BulletPattern* patternToAdd,
		Enemy* enemy) :
		EnemyAction(enemy) {
	this->patternToAdd = patternToAdd;
}

EnemyAddPatternAction::~EnemyAddPatternAction() {
	// TODO Auto-generated destructor stub
}

void EnemyAddPatternAction::update(double dt) {
	enemy->addPattern(patternToAdd);
	this->Done = true;
}
