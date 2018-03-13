/*
 * ScoreManager.cpp
 *
 *  Created on: 12/07/2013
 *      Author: Hercules
 */

#include "ScoreManager.h"

int ScoreManager::score = 0;
int ScoreManager::scoreMultiplier = 1;
Timer ScoreManager::scoreTimer;

void ScoreManager::addScoreWithMultiplier(int toAdd) {
	score += toAdd * scoreMultiplier;
}
void ScoreManager::addScore(int toAdd) {
	score += toAdd;
}
void ScoreManager::update(Shape* playerShape) {
	scoreMultiplier = GameArea::getMultiplier(playerShape);
	scoreTimer.update();
	if (scoreTimer.isDone()) {
		score += POINTS_PER_TIME * scoreMultiplier;
		scoreTimer.start(TIME_TO_ADD_SCORE);
	}
}
void ScoreManager::initialize() {
	scoreTimer.start(TIME_TO_ADD_SCORE);
	score = 0;
}
