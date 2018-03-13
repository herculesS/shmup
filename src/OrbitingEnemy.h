/*
 * OrbitingEnemy.h
 *
 *  Created on: 28/06/2013
 *      Author: Vitor
 */

#ifndef ORBITINGENEMY_H_
#define ORBITINGENEMY_H_

#include "Enemy.h"

class OrbitingEnemy: public Enemy {
private:
	float initialAngle;
	float angularSpeed;
	float radius;
	float currentRotation;
	bool clockwise;

public:
	OrbitingEnemy(Sprite* sprite, GameObject* target, Shape* shape, int life,
			Animation* hitAnimation, Enemy* orbitCenter, float initialAngle,
			float angularSpeed, float radius, bool clockwise);
	OrbitingEnemy(Enemy* enemy, Enemy* orbitCenter, float initialAngle,
			float angularSpeed, float radius, bool clockwise);
	int update(double dt);
	void explode();
	virtual ~OrbitingEnemy();
};

#endif /* ORBITINGENEMY_H_ */
