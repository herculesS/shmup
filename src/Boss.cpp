/*
 * Boss.cpp
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#include "Boss.h"

Boss::Boss(Sprite* sprite, GameObject* target, Shape* shape,
		Animation* hitAnimation) :
		Enemy(sprite, target, shape, 0, 0, hitAnimation) {
	Attacking = false;
	remainingStateTime = new Text("../ttf/Arial-Black.ttf", "0", 15, 0,
			ATTACK_TIMER_TEXT_COLOR, 0, 0);
	this->hitAnimation = hitAnimation;
	damaged = false;
}
void Boss::addBossState(BossState* state) {
	this->states.push(state);
}
void Boss::insertStateDrops() {
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
}
void Boss::setNextState() {
	this->Actions = states.front()->getEnemyToCopy()->getActions();
	setActionsOwnerAsSelf();
	this->bulletPatterns =
			states.front()->getEnemyToCopy()->getBulletPatterns();
	this->orbits = states.front()->getEnemyToCopy()->getOrbits();
	setOrbitsCenterAsSelf();
	this->setLife(states.front()->getEnemyToCopy()->getLife());
	this->drops = states.front()->getEnemyToCopy()->getDrops();
	this->shooting = false;
	remainingStateTimer.start(states.front()->getDuration());
	remainingStateTime->setColor(ATTACK_TIMER_TEXT_COLOR);
	dead = false;
}
void Boss::StartAttack() {
	if (!states.empty()) {
		setNextState();
	}
}
int Boss::update(double dt) {
	if (!Attacking) {
		Attacking = true;
		StartAttack();
	}
	Enemy::update(dt);
	if (!states.empty()) {
		remainingStateTimer.update();
		updateRemainingTimeText();
		if (remainingStateTimer.isDone()) {
			this->setDead(true);
		}
		if (dead) {
			cleanCurrentState();
			insertStateDrops();
			delete (this->states.front());
			states.pop();
			if (!states.empty()) {
				setNextState();
			}
		}
	}
	return 0;
}
void Boss::updateRemainingTimeText() {
	int RemainingTimeInSeconds, RemainingMinutes, RemainingSeconds;

	remainingStateTime->setPos(300 - remainingStateTime->getWidth() / 2,
			states.front()->getLifeBarSprite()->getHeight());
	RemainingTimeInSeconds = remainingStateTimer.remainingTime() / 1000;
	if (RemainingTimeInSeconds <= 10) {
		remainingStateTime->setColor(ATTACK_TIMER_10_TEXT_COLOR);
	}

	RemainingMinutes = RemainingTimeInSeconds / 60;
	RemainingSeconds = RemainingTimeInSeconds % 60;

	std::stringstream TextStream;
	if (RemainingMinutes <= 9) {
		TextStream << '0' << RemainingMinutes;
	} else {
		TextStream << RemainingMinutes;
	}
	TextStream << ':';
	if (RemainingSeconds <= 9) {
		TextStream << '0' << RemainingSeconds;
	} else {
		TextStream << RemainingSeconds;
	}
	remainingStateTime->setText(TextStream.str());
}
void Boss::explode() {
	if (states.empty()) {
		for (int i = 0; i < 2 * NUMBER_OF_EXPLOSIONS; i += 2) {
			Point temp1(
					rand() % EXPLOSION_RANGE
							+ this->getShape()->getCenterRef()->getX()
							- EXPLOSION_RANGE / 2,
					rand() % EXPLOSION_RANGE
							+ this->getShape()->getCenterRef()->getY()
							- EXPLOSION_RANGE / 2);
			AnimationManager::instantiate(temp1, this->onDeathExplosion.at(i));

			Point temp2(
					rand() % EXPLOSION_RANGE
							+ this->getShape()->getCenterRef()->getX()
							- EXPLOSION_RANGE / 2,
					rand() % EXPLOSION_RANGE
							+ this->getShape()->getCenterRef()->getY()
							- EXPLOSION_RANGE / 2);
			AnimationManager::instantiate(temp2, onDeathExplosion.at(i + 1));
		}
		onDeathSound->play(1);
		onDeathSound->setVolume(50);
		SoundEraser::EraseSound(onDeathSound);
	}
}
void Boss::cleanCurrentState() {
	while (!Actions.empty()) {
		delete (Actions.front());
		Actions.pop();
	}
	for (std::vector<BulletPattern*>::iterator it = bulletPatterns.begin();
			it != bulletPatterns.end(); it++) {
		delete (*it);
		it = bulletPatterns.erase(it);
		it--;
	}
	for (std::vector<Enemy*>::iterator it = orbits.begin(); it != orbits.end();
			it++) {
		(*it)->setDead(true);
	}
}
void Boss::render(float CameraX, float CameraY) {
	if (Attacking) {
		Rect gameAreaRect(Point(GAME_AREA_WIDTH / 2, GAME_AREA_HEIGHT / 2),
				GAME_AREA_WIDTH, GAME_AREA_HEIGHT);
		Enemy::render();
		remainingStateTime->render(0, 0, 0, GameArea::getSurface());
		if (life > 0) {
			int lifeScaled = life / states.front()->getLifeBarScale();
			for (int i = 0; i <= lifeScaled; i++) {
				states.front()->getLifeBarSprite()->render(
						i * states.front()->getLifeBarSprite()->getWidth(), 0,
						0, GameArea::getSurface());
			}
		}
	}
}

Boss::~Boss() {
	while (!states.empty()) {
		delete (states.front());
		states.pop();
	}
}

