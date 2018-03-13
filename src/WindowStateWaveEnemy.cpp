/*
 * WindowStateWaveEnemy.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "WindowStateWaveEnemy.h"

WindowStateWaveEnemy::WindowStateWaveEnemy(StateArgs arguments) :
		WindowState("Opcoes do inimigo") {
	enemyFileTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Arquivo do inimigo",
			arguments.getArg(0));
	xPositionTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
			"Posicao X", arguments.getArg(1));
	yPositionTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 2 * TEXT_FIELD_OFFSET),
			"Posicao Y", arguments.getArg(2));
	timeTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 3 * TEXT_FIELD_OFFSET),
			"Tempo (em milesimos)", arguments.getArg(3));

	enemyButtonImage = new Sprite("../gfx/enemyImage.png");
	enemyButtonContainer = new Sprite("../gfx/buttonContainer.png");

	enemyButton = new Button(Point(ENEMY_BUTTON_X, ENEMY_BUTTON_Y),
			enemyButtonContainer, enemyButtonImage);

}

WindowStateWaveEnemy::~WindowStateWaveEnemy() {
	delete (enemyFileTextField);
	delete (xPositionTextField);
	delete (yPositionTextField);
	delete (timeTextField);
	delete (enemyButtonImage);
	delete (enemyButtonContainer);
	delete (enemyButton);
}

int WindowStateWaveEnemy::update(double dt) {

	nextState = WindowState::STATENOCHANGE;

	enemyFileTextField->update();
	xPositionTextField->update();
	yPositionTextField->update();
	timeTextField->update();
	enemyButton->update();

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	if (enemyButton->isClicked()) {
		nextState = WindowState::STATEENEMYATTRIBUTESELECT;
	}

	return nextState;

}

void WindowStateWaveEnemy::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	enemyFileTextField->render(cameraX, cameraY);
	xPositionTextField->render(cameraX, cameraY);
	yPositionTextField->render(cameraX, cameraY);
	timeTextField->render(cameraX, cameraY);
	enemyButton->render(cameraX, cameraY);
}

StateArgs WindowStateWaveEnemy::passArguments() {
	std::vector<std::string> args;

	args.push_back(enemyFileTextField->getTextFieldString());

	return StateArgs(args);
}

StateArgs WindowStateWaveEnemy::unloadArguments() {
	std::vector<std::string> args;

	args.push_back(enemyFileTextField->getTextFieldString());
	args.push_back(xPositionTextField->getTextFieldString());
	args.push_back(yPositionTextField->getTextFieldString());
	args.push_back(timeTextField->getTextFieldString());

	return StateArgs(args);
}

void WindowStateWaveEnemy::handleUnstack(StateArgs arguments) {
	// Nada.
}
