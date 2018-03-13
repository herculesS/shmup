/*
 * WindowStateActionCreateSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateActionCreateSelect.h"

WindowStateActionCreateSelect::WindowStateActionCreateSelect(
		StateArgs arguments) :
		WindowState("Nova acao") {
	dieActionImage = new Sprite("../gfx/dieActionImage.png");
	moveActionImage = new Sprite("../gfx/moveActionImage.png");
	moveStraightActionImage = new Sprite("../gfx/moveStraightActionImage.png");
	addPatternActionImage = new Sprite("../gfx/addPatternActionImage.png");
	shootImage = new Sprite("../gfx/shootImage.png");
	stopShootingImage = new Sprite("../gfx/stopShootingImage.png");
	waitActionImage = new Sprite("../gfx/waitActionImage.png");
	buttonContainerImage = new Sprite("../gfx/buttonContainer.png");

	creatingNewAddActionPattern = false;

	dieButton = new Button(Point(ACTION_BUTTON_BASE_X, ACTION_BUTTON_BASE_Y),
			buttonContainerImage, dieActionImage);
	moveButton = new Button(
			Point(ACTION_BUTTON_BASE_X - ACTION_BUTTON_OFFSET,
					ACTION_BUTTON_BASE_Y - ACTION_BUTTON_OFFSET),
			buttonContainerImage, moveActionImage);
	moveStraightButton = new Button(
			Point(ACTION_BUTTON_BASE_X,
					ACTION_BUTTON_BASE_Y - ACTION_BUTTON_OFFSET),
			buttonContainerImage, moveStraightActionImage);
	addPatternButton = new Button(
			Point(ACTION_BUTTON_BASE_X + ACTION_BUTTON_OFFSET,
					ACTION_BUTTON_BASE_Y - ACTION_BUTTON_OFFSET),
			buttonContainerImage, addPatternActionImage);
	shootButton = new Button(
			Point(ACTION_BUTTON_BASE_X - ACTION_BUTTON_OFFSET,
					ACTION_BUTTON_BASE_Y), buttonContainerImage, shootImage);
	stopShootingButton = new Button(
			Point(ACTION_BUTTON_BASE_X + ACTION_BUTTON_OFFSET,
					ACTION_BUTTON_BASE_Y), buttonContainerImage,
			stopShootingImage);
	waitActionButton = new Button(
			Point(ACTION_BUTTON_BASE_X,
					ACTION_BUTTON_BASE_Y + ACTION_BUTTON_OFFSET),
			buttonContainerImage, waitActionImage);

}

WindowStateActionCreateSelect::~WindowStateActionCreateSelect() {
	delete (dieActionImage);
	delete (moveActionImage);
	delete (moveStraightActionImage);
	delete (addPatternActionImage);
	delete (shootImage);
	delete (stopShootingImage);
	delete (waitActionImage);
	delete (buttonContainerImage);
	delete (dieButton);
	delete (moveButton);
	delete (moveStraightButton);
	delete (addPatternButton);
	delete (shootButton);
	delete (stopShootingButton);
	delete (waitActionButton);
}

int WindowStateActionCreateSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;
	creatingNewAddActionPattern = false;
	std::vector<std::string> returningArgs;

	moveButton->update();
	moveStraightButton->update();
	dieButton->update();
	addPatternButton->update();
	shootButton->update();
	stopShootingButton->update();
	waitActionButton->update();

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	if (dieButton->isClicked()) {
		returningArgs.push_back("die");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (moveButton->isClicked()) {
		nextState = WindowState::STATEACTIONMOVE;
		returnChanges = true;
	}
	if (moveStraightButton->isClicked()) {
		nextState = WindowState::STATEACTIONMOVESTRAIGHT;
		returnChanges = true;
	}
	if (addPatternButton->isClicked()) {
		nextState = WindowState::STATEPATTERNCREATESELECT;
		creatingNewAddActionPattern = true;
		returnChanges = true;
	}
	if (shootButton->isClicked()) {
		returningArgs.push_back("shoot");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (stopShootingButton->isClicked()) {
		returningArgs.push_back("stopshooting");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (waitActionButton->isClicked()) {
		nextState = WindowState::STATEACTIONWAIT;
		returnChanges = true;
	}

	return nextState;

}

void WindowStateActionCreateSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	moveButton->render(cameraX, cameraY);
	moveStraightButton->render(cameraX, cameraY);
	dieButton->render(cameraX, cameraY);
	addPatternButton->render(cameraX, cameraY);
	shootButton->render(cameraX, cameraY);
	stopShootingButton->render(cameraX, cameraY);
	waitActionButton->render(cameraX, cameraY);
}

StateArgs WindowStateActionCreateSelect::unloadArguments() {
	return argumentsToReturn;
}

StateArgs WindowStateActionCreateSelect::passArguments() {
	std::vector<std::string> passingArguments;

	for (int i = 0; i < 10; i++) {
		passingArguments.push_back("");
	}

	return StateArgs(passingArguments);
}

void WindowStateActionCreateSelect::handleUnstack(StateArgs arguments) {

	if (creatingNewAddActionPattern) {
		arguments.setArg(0, "add");
	}

	argumentsToReturn = arguments;
}
