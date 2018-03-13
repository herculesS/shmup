/*
 * BossState.cpp
 *
 *  Created on: 30/06/2013
 *      Author: Hercules
 */

#include "BossState.h"

BossState::BossState(Enemy* toCopy, Sprite* lifeBarSprite, int duration) {
	this->toCopy = toCopy;
	this->lifeBarScale = (float) toCopy->getLife() / GAME_AREA_WIDTH;
	this->lifeBarSprite = lifeBarSprite;
	this->duration = duration;
}

float BossState::getLifeBarScale() {
	return this->lifeBarScale;
}
int BossState::getDuration() {
	return duration;
}
Sprite* BossState::getLifeBarSprite() {
	return this->lifeBarSprite;
}
Enemy* BossState::getEnemyToCopy() {
	return toCopy;
}
BossState::~BossState() {
}

