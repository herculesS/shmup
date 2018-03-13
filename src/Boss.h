/*
 * Boss.h
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#ifndef BOSS_H_
#define BOSS_H_

#include "Enemy.h"
#include "OrbitingEnemy.h"
#include "BossState.h"
#include "GameArea.h"
#include "CollisionManager.h"
#include "Rect.h"
#include "Text.h"
#include <sstream>
#define EXPLOSION_RANGE 300
#define NUMBER_OF_EXPLOSIONS 5
#define ATTACK_TIMER_TEXT_COLOR (SDL_Color){255,255,255}
#define ATTACK_TIMER_10_TEXT_COLOR (SDL_Color){255,0,0}

class Boss: public Enemy {
private:
	std::queue<BossState*, std::deque<BossState*> > states;
	Timer remainingStateTimer;
	Text* remainingStateTime;
	bool Attacking;
	void cleanCurrentState();
	void updateRemainingTimeText();
	void StartAttack();
	void setNextState();
public:
	Boss(Sprite* sprite, GameObject* target, Shape* shape,
			Animation* hitAnimation);
	void addBossState(BossState* state);
	void insertStateDrops();
	int update(double dt);
	void render(float CameraX, float CameraY);
	void explode();
	virtual ~Boss();
};

#endif /* BOSS_H_ */
