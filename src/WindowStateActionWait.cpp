/*
 * WindowStateActionWait.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateActionWait.h"

WindowStateActionWait::WindowStateActionWait(StateArgs arguments) :
		WindowState("Acao Wait") {
	timeTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Tempo (em milesimos)",
			arguments.getArg(1));
}

WindowStateActionWait::~WindowStateActionWait() {
	delete (timeTextField);
}

int WindowStateActionWait::update(double dt) {

	timeTextField->update();

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateActionWait::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	timeTextField->render(cameraX, cameraY);
}

StateArgs WindowStateActionWait::unloadArguments() {
	std::vector<std::string> argumentsToReturn;

	argumentsToReturn.push_back("wait");
	argumentsToReturn.push_back(timeTextField->getTextFieldString());

	return StateArgs(argumentsToReturn);
}

void WindowStateActionWait::handleUnstack(StateArgs arguments) {
	// Nada.
}

StateArgs WindowStateActionWait::passArguments() {
	return StateArgs();
}
