/*
 * WindowStateActionMoveStraight.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateActionMoveStraight.h"

WindowStateActionMoveStraight::WindowStateActionMoveStraight(
		StateArgs arguments) :
		WindowState("Acao MoveStraight") {
	heightTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Altura",
			arguments.getArg(1));
	speedTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
			"Velocidade", arguments.getArg(2));
}

WindowStateActionMoveStraight::~WindowStateActionMoveStraight() {
	delete (heightTextField);
	delete (speedTextField);
}

int WindowStateActionMoveStraight::update(double dt) {

	heightTextField->update();
	speedTextField->update();

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateActionMoveStraight::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	heightTextField->render(cameraX, cameraY);
	speedTextField->render(cameraX, cameraY);
}

StateArgs WindowStateActionMoveStraight::unloadArguments() {
	std::vector<std::string> argumentsToReturn;

	argumentsToReturn.push_back("movestraight");
	argumentsToReturn.push_back(heightTextField->getTextFieldString());
	argumentsToReturn.push_back(speedTextField->getTextFieldString());

	return StateArgs(argumentsToReturn);
}

void WindowStateActionMoveStraight::handleUnstack(StateArgs arguments) {
	// Nada.
}

StateArgs WindowStateActionMoveStraight::passArguments() {
	return StateArgs();
}
