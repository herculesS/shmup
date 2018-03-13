/*
 * WindowStatePatternBurst.cpp
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#include "WindowStatePatternBurst.h"

WindowStatePatternBurst::WindowStatePatternBurst(StateArgs arguments) :
		WindowState("Pattern Burst") {
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
	numRepeatsTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 3 * TEXT_FIELD_OFFSET),
			"Numero de repeticoes", arguments.getArg(5));
	bulletSpriteIndexTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 4 * TEXT_FIELD_OFFSET),
			"Indice do sprite de tiro", arguments.getArg(6));
	circularBulletCheckbox = new LabeledCheckbox(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 5 * TEXT_FIELD_OFFSET),
			"Tiro circular",
			strcasecmp(arguments.getArg(7).c_str(), "circular") == 0);
}

WindowStatePatternBurst::~WindowStatePatternBurst() {
	delete (numShotsTextField);
	delete (shotVelocityTextField);
	delete (waitTimeTextField);
	delete (numRepeatsTextField);
	delete (bulletSpriteIndexTextField);
	delete (circularBulletCheckbox);
}

int WindowStatePatternBurst::update(double dt) {

	numShotsTextField->update();
	shotVelocityTextField->update();
	waitTimeTextField->update();
	numRepeatsTextField->update();
	bulletSpriteIndexTextField->update();
	circularBulletCheckbox->update();

	nextState = WindowState::STATENOCHANGE;

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStatePatternBurst::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	numShotsTextField->render(cameraX, cameraY);
	shotVelocityTextField->render(cameraX, cameraY);
	waitTimeTextField->render(cameraX, cameraY);
	numRepeatsTextField->render(cameraX, cameraY);
	bulletSpriteIndexTextField->render(cameraX, cameraY);
	circularBulletCheckbox->render(cameraX, cameraY);
}

void WindowStatePatternBurst::handleUnstack(StateArgs arguments) {
	// Zilch
}

StateArgs WindowStatePatternBurst::unloadArguments() {
	std::vector<std::string> returnArguments;
	returnArguments.push_back("pattern");
	returnArguments.push_back("burst");
	returnArguments.push_back(numShotsTextField->getTextFieldString());
	returnArguments.push_back(shotVelocityTextField->getTextFieldString());
	returnArguments.push_back(waitTimeTextField->getTextFieldString());
	returnArguments.push_back(numRepeatsTextField->getTextFieldString());
	returnArguments.push_back(bulletSpriteIndexTextField->getTextFieldString());
	returnArguments.push_back(
			circularBulletCheckbox->isSelected() ? "circular" : "rectangular");

	return StateArgs(returnArguments);
}

StateArgs WindowStatePatternBurst::passArguments() {
	return StateArgs();
}
