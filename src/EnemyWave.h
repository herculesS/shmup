/*
 * EnemyWave.h
 *
 *  Created on: Jun 26, 2013
 *      Author: AT WORK
 */

#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_
#include "Enemy.h"
#include "Timer.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "BombManager.h"
#include <vector>

class EnemyWave {
private:
	std::vector<Enemy*> Enemies;
	std::vector<unsigned int> TimeToWaitQueue;
	std::vector<Timer> timerQueue;
	bool finished;
	int numOfKilledEnemies;

	bool valueInRange(float value, float min, float max);

public:
	EnemyWave();
	void AddEnemy(Enemy* enemy, int wait);
	void start();
	void update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void checkCollision(float areaWidth, float areaHeight);
	bool isFinished();
	Point* getClosestEnemyPosition(Point* toCheck, float areaWidth,
			float areaHeight);
	virtual ~EnemyWave();
	int getNumOfKilledEnemies() {
		return numOfKilledEnemies;
	}
};

#endif /* ENEMYWAVE_H_ */
