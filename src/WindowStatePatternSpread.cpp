/*
 * WindowStatePatternSpread.cpp
 *
 *  Created on: 25/07/2013
 *      Author: Vitor
 */

#include "WindowStatePatternSpread.h"

WindowStatePatternSpread::WindowStatePatternSpread(StateArgs arguments) :
		WindowState("Pattern Spread") {
	returnChanges = false;

	numShotsTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Numero de tiros",
			arguments.getArg(2));
	shotVelocityTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
			"Velocidade do tiro", arguments.getArg(3));
	waitTimeTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 2 * TEXT_FIELD_OFFSET),
			"Tempo de espera", arguments.getArg(4));
	arcTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 3 * TEXT_FIELD_OFFSET),
			"Angulo do arco", arguments.getArg(5));
	numRepeatsTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 4 * TEXT_FIELD_OFFSET),
			"Numero de repeticoes", arguments.getArg(6));
	bulletSpriteIndexTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 5 * TEXT_FIELD_OFFSET),
			"Indice do sprite de tiro", arguments.getArg(7));
	circularBulletCheckbox = new LabeledCheckbox(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 6 * TEXT_FIELD_OFFSET),
			"Tiro circular",
			strcasecmp(arguments.getArg(8).c_str(), "circular") == 0);
}

WindowStatePatternSpread::~WindowStatePatternSpread() {
	delete (numShotsTextField);
	delete (shotVelocityTextField);
	delete (waitTimeTextField);
	delete (arcTextField);
	delete (numRepeatsTextField);
	delete (bulletSpriteIndexTextField);
	delete (circularBulletCheckbox);
}

int WindowStatePatternSpread::update(double dt) {

	numShotsTextField->update();
	shotVelocityTextField->update();
	waitTimeTextField->update();
	arcTextField->update();
	numRepeatsTextField->update();
	bulletSpriteIndexTextField->update();
	circularBulletCheckbox->update();

	nextState = WindowState::STATENOCHANGE;

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStatePatternSpread::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	numShotsTextField->render(cameraX, cameraY);
	shotVelocityTextField->render(cameraX, cameraY);
	waitTimeTextField->render(cameraX, cameraY);
	arcTextField->render(cameraX, cameraY);
	numRepeatsTextField->render(cameraX, cameraY);
	bulletSpriteIndexTextField->render(cameraX, cameraY);
	circularBulletCheckbox->render(cameraX, cameraY);
}

void WindowStatePatternSpread::handleUnstack(StateArgs arguments) {
	// Zilch
}

StateArgs WindowStatePatternSpread::unloadArguments() {
	std::vector<std::string> returnArguments;
	returnArguments.push_back("pattern");
	returnArguments.push_back("spread");
	returnArguments.push_back(numShotsTextField->getTextFieldString());
	returnArguments.push_back(shotVelocityTextField->getTextFieldString());
	returnArguments.push_back(waitTimeTextField->getTextFieldString());
	returnArguments.push_back(arcTextField->getTextFieldString());
	returnArguments.push_back(numRepeatsTextField->getTextFieldString());
	returnArguments.push_back(bulletSpriteIndexTextField->getTextFieldString());
	returnArguments.push_back(
			circularBulletCheckbox->isSelected() ? "circular" : "rectangular");

	return StateArgs(returnArguments);
}

StateArgs WindowStatePatternSpread::passArguments() {
	return StateArgs();
}
