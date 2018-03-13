/*
 * EnemyMoveAction.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#include "EnemyMoveAction.h"

EnemyMoveAction::EnemyMoveAction(Point toMove, int speed, Enemy *enemy) :
		EnemyAction(enemy) {
	this->toMove = toMove;
	this->speed = speed;
}

EnemyMoveAction::~EnemyMoveAction() {
}

void EnemyMoveAction::update(double dt) {
	vecVel.setX(toMove.getX() - enemy->getShape()->getX());
	vecVel.setY(toMove.getY() - enemy->getShape()->getY());
	vecVel = vecVel.normalize();
	vecVel = vecVel.constantProduct(speed);

	enemy->getShape()->setX(enemy->getShape()->getX() + vecVel.getX() * dt);
	enemy->getShape()->setY(enemy->getShape()->getY() + vecVel.getY() * dt);
	if (enemy->getShape()->getCenterRef()->distanceSquared(toMove) < 100) {
		this->Done = true;
	}

}
