/*
 * Bomb.h
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "GameObject.h"
#include "Circle.h"
#include "Point.h"
#include "Killable.h"
#include "Timer.h"
#include "AnimationManager.h"

#define EXPLOSION_INITIAL_RADIUS 30.0
#define EXPLOSION_INCREASE_SPEED 200.0
#define MAX_EXPLOSION_RADIUS 400.0
#define EXPLOSION_TIME 300
#define EXPLOSION_DIFF_ANGLE 15

#define BOMB_DAMAGE 10

class Bomb: public GameObject {
private:
	Circle* explosionCircle;
	Timer explosionTimer;
	bool finished;

public:
	Bomb(Point center);
	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);

	void onCollisionWithKillable(Killable* killable);

	bool isFinished() const {
		return finished;
	}
};

#endif /* BOMB_H_ */
