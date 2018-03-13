/*
 * WindowStatePatternCreateSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStatePatternCreateSelect.h"

WindowStatePatternCreateSelect::WindowStatePatternCreateSelect(
		StateArgs arguments) :
		WindowState("Novo Pattern") {
	spreadButtonImage = new Sprite("../gfx/spreadPatternImage.png");
	burstButtonImage = new Sprite("../gfx/burstPatternImage.png");
	flowerButtonImage = new Sprite("../gfx/flowerPatternImage.png");
	buttonContainerImage = new Sprite("../gfx/buttonContainer.png");

	newBurstButton = new Button(Point(BUTTONS_BASE_X, BUTTONS_BASE_Y),
			buttonContainerImage, burstButtonImage);
	newFlowerButton = new Button(
			Point(BUTTONS_BASE_X - BUTTON_OFFSET, BUTTONS_BASE_Y),
			buttonContainerImage, flowerButtonImage);
	newSpreadButton = new Button(
			Point(BUTTONS_BASE_X + BUTTON_OFFSET, BUTTONS_BASE_Y),
			buttonContainerImage, spreadButtonImage);
}

WindowStatePatternCreateSelect::~WindowStatePatternCreateSelect() {
	delete (spreadButtonImage);
	delete (burstButtonImage);
	delete (flowerButtonImage);
	delete (buttonContainerImage);
	delete (newBurstButton);
	delete (newFlowerButton);
	delete (newSpreadButton);
}

int WindowStatePatternCreateSelect::update(double dt) {

	newBurstButton->update();
	newFlowerButton->update();
	newSpreadButton->update();

	nextState = WindowState::STATENOCHANGE;

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}
	if (newBurstButton->isClicked()) {
		nextState = WindowState::STATEPATTERNBURST;
		returnChanges = true;
	}
	if (newFlowerButton->isClicked()) {
		nextState = WindowState::STATEPATTERNFLOWER;
		returnChanges = true;
	}
	if (newSpreadButton->isClicked()) {
		nextState = WindowState::STATEPATTERNSPREAD;
		returnChanges = true;
	}

	return nextState;
}

void WindowStatePatternCreateSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	newBurstButton->render(cameraX, cameraY);
	newFlowerButton->render(cameraX, cameraY);
	newSpreadButton->render(cameraX, cameraY);
}

StateArgs WindowStatePatternCreateSelect::passArguments() {

	std::vector<std::string> argumentsToPass;

	for (int i = 0; i < 10; i++) {
		argumentsToPass.push_back("");
	}

	return StateArgs(argumentsToPass);
}

void WindowStatePatternCreateSelect::handleUnstack(StateArgs arguments) {
	returnArguments = arguments;
}

StateArgs WindowStatePatternCreateSelect::unloadArguments() {
	return returnArguments;
}
