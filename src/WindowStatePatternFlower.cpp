/*
 * WindowStatePatternFlower.cpp
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#include "WindowStatePatternFlower.h"

WindowStatePatternFlower::WindowStatePatternFlower(StateArgs arguments) :
		WindowState("Pattern Flower") {
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
	angleTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 3 * TEXT_FIELD_OFFSET),
			"Angulo entre tiros", arguments.getArg(5));
	numRepeatsTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 4 * TEXT_FIELD_OFFSET),
			"Numero de repeticoes", arguments.getArg(6));
	bulletSpriteIndexTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 5 * TEXT_FIELD_OFFSET),
			"Indice do sprite de tiro", arguments.getArg(8));
	circularBulletCheckbox = new LabeledCheckbox(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 6 * TEXT_FIELD_OFFSET),
			"Tiro circular",
			strcasecmp(arguments.getArg(9).c_str(), "circular") == 0);
	clockwiseCheckbox = new LabeledCheckbox(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 7 * TEXT_FIELD_OFFSET),
			"Sentido horario",
			strcasecmp(arguments.getArg(7).c_str(), "clk") == 0);

}

WindowStatePatternFlower::~WindowStatePatternFlower() {
	delete (numShotsTextField);
	delete (shotVelocityTextField);
	delete (waitTimeTextField);
	delete (angleTextField);
	delete (numRepeatsTextField);
	delete (bulletSpriteIndexTextField);
	delete (circularBulletCheckbox);
	delete (clockwiseCheckbox);
}

int WindowStatePatternFlower::update(double dt) {

	numShotsTextField->update();
	shotVelocityTextField->update();
	waitTimeTextField->update();
	angleTextField->update();
	numRepeatsTextField->update();
	bulletSpriteIndexTextField->update();
	circularBulletCheckbox->update();
	clockwiseCheckbox->update();

	nextState = WindowState::STATENOCHANGE;

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;

}

void WindowStatePatternFlower::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	numShotsTextField->render(cameraX, cameraY);
	shotVelocityTextField->render(cameraX, cameraY);
	waitTimeTextField->render(cameraX, cameraY);
	angleTextField->render(cameraX, cameraY);
	numRepeatsTextField->render(cameraX, cameraY);
	bulletSpriteIndexTextField->render(cameraX, cameraY);
	circularBulletCheckbox->render(cameraX, cameraY);
	clockwiseCheckbox->render(cameraX, cameraY);

}

StateArgs WindowStatePatternFlower::unloadArguments() {
	std::vector<std::string> argumentsToReturn;

	argumentsToReturn.push_back("pattern");
	argumentsToReturn.push_back("flower");
	argumentsToReturn.push_back(numShotsTextField->getTextFieldString());
	argumentsToReturn.push_back(shotVelocityTextField->getTextFieldString());
	argumentsToReturn.push_back(waitTimeTextField->getTextFieldString());
	argumentsToReturn.push_back(angleTextField->getTextFieldString());
	argumentsToReturn.push_back(numRepeatsTextField->getTextFieldString());
	argumentsToReturn.push_back(
			clockwiseCheckbox->isSelected() ? "clk" : "aclk");
	argumentsToReturn.push_back(
			bulletSpriteIndexTextField->getTextFieldString());
	argumentsToReturn.push_back(
			circularBulletCheckbox->isSelected() ? "circular" : "rectangular");

	return StateArgs(argumentsToReturn);
}

void WindowStatePatternFlower::handleUnstack(StateArgs arguments) {
	// Zilch.
}

StateArgs WindowStatePatternFlower::passArguments() {
	return StateArgs();
}
