/*
 * Enemy.h
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"
#include "GameArea.h"
#include "Sprite.h"
#include "BulletPattern.h"
#include "Droppable.h"
#include "DropManager.h"
#include "AnimationManager.h"
#include "ScoreManager.h"
#include "Killable.h"
#include "Sound.h"
#include "SoundEraser.h"
#include <vector>
#include <queue>
#include <deque>

#define DROP_RADIUS 100
#define HIT_ANIMATION_TIME 200

class EnemyAction;

class Enemy: public Killable {
protected:
	std::queue<EnemyAction*, std::deque<EnemyAction*> > Actions;
	std::vector<BulletPattern*> bulletPatterns;
	std::vector<Enemy*> orbits;
	std::vector<Droppable*> drops;
	GameObject* target;
	Enemy* orbitCenter;
	Sprite* sprite;
	Sound* onDeathSound;
	std::vector<Animation*> onDeathExplosion;
	Animation* hitAnimation;
	Timer hitAnimationTimer;
	bool damaged;
	bool shooting;
	int scorePoints;

public:
	Enemy(Sprite* sprite, GameObject* target, Shape* shape, int life,
			int points, Animation* hitAnimation);
	virtual int update(double dt);
	void AddAction(EnemyAction* action);
	void addPattern(BulletPattern* bulletPattern);
	void addOrbit(Enemy* orbit);
	virtual void render(float cameraX = 0, float cameraY = 0);
	virtual void onDeath();
	virtual void explode();
	void attemptToKill(int damage);
	virtual ~Enemy();

	void setActionsOwnerAsSelf();
	void setOrbitsCenterAsSelf();
	void addExplosionAnimation(Animation* toAdd);
	void clearDrops();

	std::queue<EnemyAction*, std::deque<EnemyAction*> > getActions();
	std::vector<BulletPattern*> getBulletPatterns();
	std::vector<Enemy*> getOrbits();
	std::vector<Droppable*> getDrops();

	void setShooting(bool shooting) {
		this->shooting = shooting;
	}

	void setBulletPatterns(std::vector<BulletPattern*> bulletPatterns) {
		this->bulletPatterns = bulletPatterns;
	}

	void setActions(
			std::queue<EnemyAction*, std::deque<EnemyAction*> > actions) {
		Actions = actions;
	}
	void setCenter(Enemy* newCenter) {
		orbitCenter = newCenter;
	}

	void setScorePoints(int toSet) {
		this->scorePoints = toSet;
	}

	void setOrbits(std::vector<Enemy*> orbits) {
		this->orbits = orbits;
	}

	void setDrops(std::vector<Droppable*> drops) {
		this->drops = drops;
	}
};

class EnemyAction {
protected:
	Enemy *enemy;
	bool Done;
public:
	EnemyAction(Enemy* enemy);
	virtual void update(double dt) = 0;
	bool isDone() {
		return Done;
	}
	virtual ~EnemyAction();

	void setEnemy(Enemy* enemy) {
		this->enemy = enemy;
	}
};

#endif /* ENEMY_H_ */
