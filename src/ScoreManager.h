/*
 * ScoreManager.h
 *
 *  Created on: 12/07/2013
 *      Author: Hercules
 */

#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_
#include "GameArea.h"
#include "Timer.h"

#define TIME_TO_ADD_SCORE 1000
#define POINTS_PER_TIME 10

class ScoreManager {
private:
	static int score;
	static int scoreMultiplier;
	static Timer scoreTimer;
public:
	static void addScoreWithMultiplier(int toAdd);
	static void addScore(int toAdd);
	static int getScore() {
		return score;
	}
	static int getScoreMultiplier() {
		return scoreMultiplier;
	}
	static void update(Shape* playerShape);
	static void initialize();
};

#endif /* SCOREMANAGER_H_ */
