/*
 * EnemyMoveStraightAction.cpp
 *
 *  Created on: 20/07/2013
 *      Author: vitor
 */

#include "EnemyMoveStraightAction.h"

EnemyMoveStraightAction::EnemyMoveStraightAction(float yToMove, int speed,
		Enemy* enemy) :
		EnemyAction(enemy) {
	this->yToMove = yToMove;
	this->speed = speed;
}

EnemyMoveStraightAction::~EnemyMoveStraightAction() {
	// TODO Auto-generated destructor stub
}

void EnemyMoveStraightAction::update(double dt) {

	vecVel.setY(yToMove - enemy->getShape()->getY());
	vecVel = vecVel.normalize().constantProduct(speed);

	enemy->getShape()->setCenter(
			enemy->getShape()->getCenterRef()->addVector(
					vecVel.constantProduct(dt)));

	if (fabs(enemy->getShape()->getY() - yToMove) < 10) {
		Done = true;
	}
}
