/*
 * EnemyMoveStraightAction.h
 *
 *  Created on: 20/07/2013
 *      Author: vitor
 */

#ifndef ENEMYMOVESTRAIGHTACTION_H_
#define ENEMYMOVESTRAIGHTACTION_H_

#include "Enemy.h"
#include "Vector2.h"

class EnemyMoveStraightAction: public EnemyAction {
private:
	float yToMove;
	Vector2 vecVel;
	int speed;

public:
	EnemyMoveStraightAction(float yToMove, int speed, Enemy* enemy);
	virtual ~EnemyMoveStraightAction();

	void update(double dt);
};

#endif /* ENEMYMOVESTRAIGHTACTION_H_ */
