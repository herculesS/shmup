/*
 * WindowStateActionMove.cpp
 *
 *  Created on: 25/07/2013
 *      Author: Vitor
 */

#include "WindowStateActionMove.h"

WindowStateActionMove::WindowStateActionMove(StateArgs arguments) :
		WindowState("Acao Move") {
	returnChanges = false;

	xPositionTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Posicao X",
			arguments.getArg(1));
	yPositionTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
			"Posicao Y", arguments.getArg(2));
	speedTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 2 * TEXT_FIELD_OFFSET),
			"Velocidade", arguments.getArg(3));

}

WindowStateActionMove::~WindowStateActionMove() {
	delete (xPositionTextField);
	delete (yPositionTextField);
	delete (speedTextField);
}

int WindowStateActionMove::update(double dt) {

	xPositionTextField->update();
	yPositionTextField->update();
	speedTextField->update();

	nextState = WindowState::STATENOCHANGE;

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateActionMove::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	xPositionTextField->render(cameraX, cameraY);
	yPositionTextField->render(cameraX, cameraY);
	speedTextField->render(cameraX, cameraY);
}

StateArgs WindowStateActionMove::unloadArguments() {
	std::vector<std::string> argumentsToReturn;

	argumentsToReturn.push_back("move");
	argumentsToReturn.push_back(xPositionTextField->getTextFieldString());
	argumentsToReturn.push_back(yPositionTextField->getTextFieldString());
	argumentsToReturn.push_back(speedTextField->getTextFieldString());

	return StateArgs(argumentsToReturn);
}

void WindowStateActionMove::handleUnstack(StateArgs arguments) {
	// Nada.
}

StateArgs WindowStateActionMove::passArguments() {
	return StateArgs();
}
