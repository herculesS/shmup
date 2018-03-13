/*
 * EnemyShootAction.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#include "EnemyShootAction.h"

EnemyShootAction::EnemyShootAction(Enemy *enemy) :
		EnemyAction(enemy) {
}

void EnemyShootAction::update(double dt) {
	enemy->setShooting(true);
	this->Done = true;
}

EnemyShootAction::~EnemyShootAction() {
}

