/*
 * Enemy.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: AT WORK
 */

#include "Enemy.h"

Enemy::Enemy(Sprite* sprite, GameObject* target, Shape* shape, int life,
		int points, Animation* hitAnimation) :
		Killable(life, shape) {
	this->sprite = sprite;
	this->shooting = false;
	this->target = target;
	this->scorePoints = points;
	this->orbitCenter = NULL;
	this->hitAnimation = hitAnimation;
	this->damaged = false;
	this->hitAnimation->setHidden(true);
	onDeathSound = new Sound("../sfx/explosion-02.wav");
}

int Enemy::update(double dt) {
	if (!Actions.empty()) {
		if (Actions.front()->isDone()) {
			delete (Actions.front());
			Actions.pop();
		}
		if (!Actions.empty())
			Actions.front()->update(dt);
	}
	if (damaged) {
		hitAnimation->update(dt);
		hitAnimationTimer.update();
		if (hitAnimationTimer.isDone()) {
			damaged = false;
			this->hitAnimation->setHidden(true);
		}
	}

	for (std::vector<Enemy*>::iterator it = orbits.begin(); it != orbits.end();
			++it) {
		(*it)->update(dt);
		if ((*it)->isDead()) {
			(*it)->onDeath();
			delete (*it);
			it = orbits.erase(it);
			it--;
		}
	}

	if (shooting) {
		for (std::vector<BulletPattern*>::iterator it = bulletPatterns.begin();
				it != bulletPatterns.end(); ++it) {
			(*it)->shoot(*(shape->getCenterRef()),
					*(target->getShape()->getCenterRef()));
		}
	}

	return 0;
}

Enemy::~Enemy() {
	while (!Actions.empty()) {
		delete (Actions.front());
		Actions.pop();
	}

	for (std::vector<BulletPattern*>::iterator it = bulletPatterns.begin();
			it != bulletPatterns.end(); ++it) {
		delete (*it);
		it = bulletPatterns.erase(it);
		it--;
	}

	for (std::vector<Enemy*>::iterator it = orbits.begin(); it != orbits.end();
			++it) {
		delete (*it);
		it = orbits.erase(it);
		it--;
	}
}

void Enemy::render(float cameraX, float cameraY) {
	this->sprite->render(this->getShape()->getCenterRef()->getX() - cameraX,
			this->getShape()->getCenterRef()->getY() - cameraY, 1,
			GameArea::getSurface());

	this->hitAnimation->render(
			this->getShape()->getCenterRef()->getX() - cameraX,
			this->getShape()->getCenterRef()->getY() - cameraY, 1,
			GameArea::getSurface());

	for (std::vector<Enemy*>::iterator it = orbits.begin(); it != orbits.end();
			++it) {
		(*it)->render();
	}
}

void Enemy::onDeath() {

	for (std::vector<Droppable*>::iterator it = drops.begin();
			it != drops.end(); ++it) {
		(*it)->getShape()->setCenter(
				Point(
						shape->getX()
								+ ((rand() % DROP_RADIUS) - DROP_RADIUS / 2),
						shape->getY()
								+ ((rand() % DROP_RADIUS) - DROP_RADIUS / 2)));
	}

	DropManager::insertDrops(drops);
	ScoreManager::addScoreWithMultiplier(this->scorePoints);
	this->explode();

}
void Enemy::explode() {
	for (std::vector<Animation*>::iterator it = onDeathExplosion.begin();
			it != onDeathExplosion.end(); it++) {
		AnimationManager::instantiate(*this->getShape()->getCenterRef(), (*it));
	}
	if (killed) {
		onDeathSound->play(1);
		onDeathSound->setVolume(30);
		SoundEraser::EraseSound(onDeathSound);
	}
}

void Enemy::AddAction(EnemyAction* action) {
	this->Actions.push(action);
}

void Enemy::addPattern(BulletPattern* bulletPattern) {
	this->bulletPatterns.push_back(bulletPattern);
}
void Enemy::addOrbit(Enemy* orbit) {
	this->orbits.push_back(orbit);
}
void Enemy::addExplosionAnimation(Animation* toAdd) {
	this->onDeathExplosion.push_back(toAdd);
}

void Enemy::clearDrops() {
	for (std::vector<Droppable*>::iterator it = drops.begin();
			it != drops.end(); ++it) {
		delete (*it);
		it = drops.erase(it);
		it--;
	}
}
std::vector<Droppable*> Enemy::getDrops() {
	return drops;
}

std::queue<EnemyAction*, std::deque<EnemyAction*> > Enemy::getActions() {
	return Actions;
}
std::vector<BulletPattern*> Enemy::getBulletPatterns() {
	return bulletPatterns;
}
std::vector<Enemy*> Enemy::getOrbits() {
	return orbits;
}

// M�todo infelizmente necess�rio para atrelar as a��es devidas
// �s �rbitas...
void Enemy::setActionsOwnerAsSelf() {
	EnemyAction* temp;
	std::queue<EnemyAction*, std::deque<EnemyAction*> > tempQueue;

	while (!Actions.empty()) {
		temp = Actions.front();
		Actions.pop();

		temp->setEnemy(this);

		tempQueue.push(temp);
	}

	Actions = tempQueue;
}
void Enemy::setOrbitsCenterAsSelf() {
	for (std::vector<Enemy*>::iterator it = orbits.begin(); it != orbits.end();
			++it) {
		(*it)->setCenter(this);
	}
}
void Enemy::attemptToKill(int damage) {
	Killable::attemptToKill(damage);
	damaged = true;
	hitAnimationTimer.start(HIT_ANIMATION_TIME);
	this->hitAnimation->setHidden(false);
}

