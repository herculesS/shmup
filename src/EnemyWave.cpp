/*
 * EnemyWave.cpp
 *
 *  Created on: Jun 26, 2013
 *      Author: AT WORK
 */

#include "EnemyWave.h"

EnemyWave::EnemyWave() {
	finished = false;
	numOfKilledEnemies = 0;
}

EnemyWave::~EnemyWave() {
	for (std::vector<Enemy*>::iterator it = Enemies.begin();
			it != Enemies.end(); ++it) {
		delete (*it);
		it = Enemies.erase(it);
		it--;
	}
}

void EnemyWave::AddEnemy(Enemy *enemy, int wait) {
	Enemies.push_back(enemy);
	TimeToWaitQueue.push_back(wait);
	timerQueue.push_back(Timer());
}

void EnemyWave::start() {
	for (unsigned int i = 0; i < Enemies.size(); i++) {
		timerQueue.at(i).start(TimeToWaitQueue.at(i));
	}
}

void EnemyWave::update(double dt) {
	for (unsigned int i = 0; i < Enemies.size(); i++) {
		timerQueue.at(i).update();
		if (timerQueue.at(i).isDone()) {
			Enemies.at(i)->update(dt);
			if (Enemies.at(i)->isDead()) {
				if (Enemies.at(i)->wasKilled()) {
					numOfKilledEnemies++;
				}
				Enemies.at(i)->onDeath();
				delete (Enemies.at(i));
				Enemies.erase(Enemies.begin() + i);

				TimeToWaitQueue.erase(TimeToWaitQueue.begin() + i);
				timerQueue.erase(timerQueue.begin() + i);
				i--;
			}
			if (Enemies.size() == 0) {
				finished = true;
			}
		}
	}
}
bool EnemyWave::isFinished() {
	return finished;
}

void EnemyWave::checkCollision(float areaWidth, float areaHeight) {

	Bullet* tempBullet;

	for (std::vector<Enemy*>::iterator it = Enemies.begin();
			it != Enemies.end(); it++) {
		if ((tempBullet = BulletManager::checkCollision((*it), true)) != NULL) {
			tempBullet->onCollisionWith((*it));
		}

		// Checa se o inimigo está dentro da tela e causa dano com a bomba
		// caso esteja.
		if (valueInRange((*it)->getShape()->getX(), 0, areaWidth)
				&& valueInRange((*it)->getShape()->getY(), 0, areaHeight)
				&& BombManager::checkCollision((*it))) {
			BombManager::getBomb()->onCollisionWithKillable((*it));
		}
	}

}
Point* EnemyWave::getClosestEnemyPosition(Point* toCheck, float areaWidth,
		float areaHeight) {
	Point* toReturn = NULL;
	float minDistance = 999999;
	if (Enemies.empty()) {
		return NULL;
	}
	for (std::vector<Enemy*>::iterator it = Enemies.begin();
			it != Enemies.end(); it++) {
		if ((valueInRange((*it)->getShape()->getX(), 0, areaWidth)
				&& valueInRange((*it)->getShape()->getY(), 0, areaHeight))
				&& (*it)->getShape()->getCenterRef()->distance(*toCheck)
						< minDistance) {
			minDistance = (*it)->getShape()->getCenterRef()->distance(*toCheck);
			toReturn = (*it)->getShape()->getCenterRef();
		}
	}
	return toReturn;
}

bool EnemyWave::valueInRange(float value, float min, float max) {
	return value >= min && value <= max;
}

void EnemyWave::render(float cameraX, float cameraY) {
	for (std::vector<Enemy*>::iterator it = Enemies.begin();
			it != Enemies.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}
}
