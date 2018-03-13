/*
 * WindowStateDroppableUpgrade.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateDroppableUpgrade.h"

WindowStateDroppableUpgrade::WindowStateDroppableUpgrade(StateArgs arguments) :
		WindowState("Drop upgrade") {
	dropNumberTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Numero de drops",
			arguments.getArg(1));
}

WindowStateDroppableUpgrade::~WindowStateDroppableUpgrade() {
	delete (dropNumberTextField);
}

int WindowStateDroppableUpgrade::update(double dt) {

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	dropNumberTextField->update();

	return nextState;
}

void WindowStateDroppableUpgrade::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	dropNumberTextField->render(cameraX, cameraY);
}

StateArgs WindowStateDroppableUpgrade::passArguments() {
	return StateArgs();
}

void WindowStateDroppableUpgrade::handleUnstack(StateArgs arguments) {
	// Nada.
}

StateArgs WindowStateDroppableUpgrade::unloadArguments() {
	std::vector<std::string> argumentsToReturn;

	argumentsToReturn.push_back("upgrade");
	argumentsToReturn.push_back(dropNumberTextField->getTextFieldString());

	return StateArgs(argumentsToReturn);
}
