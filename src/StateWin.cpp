/*
 * StateWin.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Hercules
 */

#include "StateWin.h"

StateWin::StateWin() {
	// TODO Auto-generated constructor stub

}
void StateWin::load(StateArgs arguments) {
	background = new Sprite("../gfx/stateMenu.jpg");
	scoreBox = new Sprite("../gfx/ScoreBox.png");
	buttonSprite = new Sprite("../gfx/stateWinButton.png");
	SDL_Color textColor;
	textColor.b = 0;
	textColor.g = 255;
	textColor.r = 255;

	Rect scoreRect(SDLBase::getScreen()->w / 2 - scoreBox->getWidth() / 2,
			SDLBase::getScreen()->h / 2 - scoreBox->getHeight() / 2,
			scoreBox->getWidth(), scoreBox->getHeight());
	continueButtonPositon = new Point(
			scoreRect.getX() + LABEL_OFFSET + buttonSprite->getWidth() / 2,
			scoreRect.getY() + scoreRect.getH()
					- buttonSprite->getHeight() / 2);
	quitButtonPosition = new Point(
			scoreRect.getX() + scoreRect.getW() - LABEL_OFFSET
					- buttonSprite->getWidth() / 2,
			scoreRect.getY() + scoreRect.getH()
					- buttonSprite->getHeight() / 2);
	quitButtonText = new Text(FONT, "Quit", 20, 0, textColor,
			quitButtonPosition->getX(), quitButtonPosition->getY());
	continueButtonText = new Text(FONT, "Continue", 20, 0, textColor,
			continueButtonPositon->getX(), continueButtonPositon->getY());
	titleText = new Text(FONT, "Stage Clear!", 25, 0, textColor,
			scoreRect.getX() + TITLE_X_OFFSET,
			scoreRect.getY() + TITLE_Y_OFFSET);
	killedEnemiesLabel = new Text(FONT, "Enemies Killed:", 25, 0, textColor,
			scoreRect.getX() + LABEL_OFFSET,
			scoreRect.getY() + DISTANCE_BETWEEN_LABEL);
	killedEnemiesPoints = new Text(FONT, arguments.getArg(0), 25, 0, textColor,
			scoreRect.getX() + POINTS_OFFSET,
			scoreRect.getY() + DISTANCE_BETWEEN_LABEL);

	std::stringstream LiveBonusText, BombsBonusText, BonusText, scoreText;

	LiveBonusText << arguments.getArg(1) << 'x' << 100;
	playerLivesLabel = new Text(FONT, "Lives:", 25, 0, textColor,
			scoreRect.getX() + LABEL_OFFSET,
			scoreRect.getY() + 2 * DISTANCE_BETWEEN_LABEL);
	playerLivesPoints = new Text(FONT, LiveBonusText.str(), 25, 0, textColor,
			scoreRect.getX() + POINTS_OFFSET,
			scoreRect.getY() + 2 * DISTANCE_BETWEEN_LABEL);

	BombsBonusText << arguments.getArg(2) << 'x' << 100;
	playerBombsLabel = new Text(FONT, "Bombs:", 25, 0, textColor,
			scoreRect.getX() + LABEL_OFFSET,
			scoreRect.getY() + 3 * DISTANCE_BETWEEN_LABEL);
	playerBombsPoints = new Text(FONT, BombsBonusText.str(), 25, 0, textColor,
			scoreRect.getX() + POINTS_OFFSET,
			scoreRect.getY() + 3 * DISTANCE_BETWEEN_LABEL);

	bonusScore = atoi(arguments.getArg(1).c_str()) * 100
			+ atoi(arguments.getArg(2).c_str()) * 100;

	BonusText << bonusScore;
	bonusScoreLabel = new Text(FONT, "Bonus:", 25, 0, textColor,
			scoreRect.getX() + LABEL_OFFSET,
			scoreRect.getY() + 4 * DISTANCE_BETWEEN_LABEL);
	bonusScorePoints = new Text(FONT, BonusText.str(), 25, 0, textColor,
			scoreRect.getX() + POINTS_OFFSET,
			scoreRect.getY() + 4 * DISTANCE_BETWEEN_LABEL);

	scoreText << ScoreManager::getScore();
	scoreLabel =
			new Text(FONT, "Total Score:", 25, 0, textColor,
					scoreRect.getX() + TITLE_X_OFFSET,
					scoreRect.getY() + 5 * DISTANCE_BETWEEN_LABEL + TOTAL_SCORE_OFFSET);scorePoints
	=
			new Text(FONT, scoreText.str(), 25, 0, textColor,
					scoreRect.getX() + POINTS_OFFSET,
					scoreRect.getY() + 5 * DISTANCE_BETWEEN_LABEL + TOTAL_SCORE_OFFSET);

					killedEnemiesTimer
	.start(1000);
	livesTimer.start(2000);
	bombsTimer.start(3000);
	bonusScoreTimer.start(4000);
	TotalScoreTimer.start(5000);
	shouldShowKilledEnemies = false;
	shouldShowLives = false;
	shouldShowBombs = false;
	shouldShowBonusScore = false;
	quitGame = false;
	m_continue = false;
	buttonsActivated = false;
	pointsAdd = 0;
}
StateArgs StateWin::unload() {
	delete titleText;
	delete scoreLabel;
	delete scorePoints;
	delete killedEnemiesLabel;
	delete killedEnemiesPoints;
	delete playerLivesLabel;
	delete playerLivesPoints;
	delete playerBombsLabel;
	delete playerBombsPoints;
	delete bonusScoreLabel;
	delete bonusScorePoints;
	delete background;
	delete scoreBox;
	delete buttonSprite;
	delete quitButtonText;
	delete continueButtonText;
	delete quitButtonPosition;
	delete continueButtonPositon;
	return StateArgs();
}
void StateWin::input() {
	if (InputManager::getInstance()->QuitGame()) {
		quitGame = true;
	}
	if (buttonsActivated) {
		SDL_Rect quitRect, continueRect;
		quitRect.x = quitButtonPosition->getX() - buttonSprite->getWidth() / 2;
		quitRect.y = quitButtonPosition->getY() - buttonSprite->getHeight() / 2;
		continueRect.x = continueButtonPositon->getX()
				- buttonSprite->getWidth() / 2;
		continueRect.y = continueButtonPositon->getY()
				- buttonSprite->getHeight() / 2;
		quitRect.w = continueRect.w = buttonSprite->getWidth();
		quitRect.h = continueRect.h = buttonSprite->getHeight();
		if (InputManager::getInstance()->isMouseInside(&quitRect)
				&& InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)) {
			quitGame = true;
		}
		if (InputManager::getInstance()->isMouseInside(&continueRect)
				&& InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)) {
			m_continue = true;
		}
	}
}
int StateWin::update(double dt) {
	std::stringstream scoreText, BonusText;

	killedEnemiesTimer.update();
	livesTimer.update();
	bombsTimer.update();
	bonusScoreTimer.update();
	TotalScoreTimer.update();

	if (killedEnemiesTimer.isDone()) {
		shouldShowKilledEnemies = true;
	}
	if (livesTimer.isDone()) {
		shouldShowLives = true;
	}
	if (bombsTimer.isDone()) {
		shouldShowBombs = true;
	}
	if (bonusScoreTimer.isDone()) {
		shouldShowBonusScore = true;
	}
	if (TotalScoreTimer.isDone()) {
		if (pointsAdd < bonusScore) {
			ScoreManager::addScore(POINTS_INCREMENT);
			scoreText << ScoreManager::getScore();
			scorePoints->setText(scoreText.str());

			pointsAdd += POINTS_INCREMENT;
			BonusText << bonusScore - pointsAdd;
			bonusScorePoints->setText(BonusText.str());
		} else {
			buttonsActivated = true;
		}
	}
	nextState = SDLBase::STATENOCHANGE;
	if (quitGame) {
		nextState = SDLBase::STATEQUIT;
	}
	if (m_continue) {
		nextState = SDLBase::STATEMENU;
	}
	return nextState;
}
void StateWin::render() {
	background->render(0, 0, 0);
	scoreBox->render(SDLBase::getScreen()->w / 2, SDLBase::getScreen()->h / 2,
			1);
	titleText->render(0, 0, 0);
	if (shouldShowKilledEnemies) {
		killedEnemiesLabel->render(0, 0, 0);
		killedEnemiesPoints->render(0, 0, 0);
	}
	if (shouldShowLives) {
		playerLivesLabel->render(0, 0, 0);
		playerLivesPoints->render(0, 0, 0);
	}
	if (shouldShowBombs) {
		playerBombsLabel->render(0, 0, 0);
		playerBombsPoints->render(0, 0, 0);
	}
	if (shouldShowBonusScore) {
		bonusScoreLabel->render(0, 0, 0);
		bonusScorePoints->render(0, 0, 0);
	}
	scoreLabel->render(0, 0, 0);
	scorePoints->render(0, 0, 0);
	if (buttonsActivated) {
		buttonSprite->render(quitButtonPosition->getX(),
				quitButtonPosition->getY(), 1);
		buttonSprite->render(continueButtonPositon->getX(),
				continueButtonPositon->getY(), 1);
		quitButtonText->render(0, 0, 1);
		continueButtonText->render(0, 0, 1);
	}
}

StateWin::~StateWin() {
// TODO Auto-generated destructor stub
}

