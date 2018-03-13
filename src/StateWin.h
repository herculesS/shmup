/*
 * StateWin.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Hercules
 */

#ifndef STATEWIN_H_
#define STATEWIN_H_

#include "State.h"
#include "Text.h"
#include "Sprite.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "Timer.h"
#include "Rect.h"
#include <sstream>
#define TITLE_X_OFFSET 10
#define TITLE_Y_OFFSET 10
#define LABEL_OFFSET 50
#define POINTS_OFFSET 400
#define DISTANCE_BETWEEN_LABEL 50
#define TOTAL_SCORE_OFFSET 50
#define POINTS_INCREMENT 10

#define FONT "../ttf/Bedbug.ttf"

class StateWin: public State {
private:
	Text* titleText;
	Text* scoreLabel;
	Text* scorePoints;
	Text* killedEnemiesLabel;
	Text* killedEnemiesPoints;
	Text* playerLivesLabel;
	Text* playerLivesPoints;
	Text* playerBombsLabel;
	Text* playerBombsPoints;
	Text* bonusScoreLabel;
	Text* bonusScorePoints;
	Sprite* background;
	Sprite* scoreBox;
	Sprite* buttonSprite;
	Text* quitButtonText;
	Text* continueButtonText;
	Timer killedEnemiesTimer;
	Timer livesTimer;
	Timer bombsTimer;
	Timer bonusScoreTimer;
	Timer TotalScoreTimer;
	Point* quitButtonPosition;
	Point* continueButtonPositon;
	bool shouldShowKilledEnemies;
	bool shouldShowLives;
	bool shouldShowBombs;
	bool shouldShowBonusScore;
	bool buttonsActivated;
	bool m_continue;
	int bonusScore;
	int pointsAdd;
	bool quitGame;
public:
	StateWin();
	void load(StateArgs arguments);
	StateArgs unload();
	void input();
	int update(double dt);
	void render();
	~StateWin();

};

#endif /* STATEWIN_H_ */
