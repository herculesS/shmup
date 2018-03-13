/*
 * EnemyMoveAction.h
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#ifndef ENEMYMOVEACTION_H_
#define ENEMYMOVEACTION_H_

#include "Enemy.h"

class EnemyMoveAction: public EnemyAction {
private:
	Point toMove;
	Vector2 vecVel;
	int speed;

public:
	EnemyMoveAction(Point toMove, int speed, Enemy *enemy);
	void update(double dt);
	virtual ~EnemyMoveAction();
};

#endif /* ENEMYMOVEACTION_H_ */
