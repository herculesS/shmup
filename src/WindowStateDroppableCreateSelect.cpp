/*
 * WindowStateDroppableCreateSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateDroppableCreateSelect.h"

WindowStateDroppableCreateSelect::WindowStateDroppableCreateSelect(
		StateArgs arguments) :
		WindowState("Novo drop") {
	laserDropImage = new Sprite("../gfx/laserDropImage.png");
	spreadDropImage = new Sprite("../gfx/spreadDropImage.png");
	missileDropImage = new Sprite("../gfx/missileDropImage.png");
	bombDropImage = new Sprite("../gfx/bombDropImage.png");
	upgradeDropImage = new Sprite("../gfx/upgradeDropImage.png");
	buttonContainer = new Sprite("../gfx/buttonContainer.png");

	laserDropButton = new Button(Point(DROP_BUTTON_BASE_X, DROP_BUTTON_BASE_Y),
			buttonContainer, laserDropImage);
	spreadDropButton = new Button(
			Point(DROP_BUTTON_BASE_X + DROP_BUTTON_OFFSET, DROP_BUTTON_BASE_Y),
			buttonContainer, spreadDropImage);
	missileDropButton = new Button(
			Point(DROP_BUTTON_BASE_X + 2 * DROP_BUTTON_OFFSET,
					DROP_BUTTON_BASE_Y), buttonContainer, missileDropImage);
	bombDropButton = new Button(
			Point(SECOND_ROW_BASE_X, DROP_BUTTON_BASE_Y + DROP_BUTTON_OFFSET),
			buttonContainer, bombDropImage);
	upgradeDropButton = new Button(
			Point(SECOND_ROW_BASE_X + DROP_BUTTON_OFFSET,
					DROP_BUTTON_BASE_Y + DROP_BUTTON_OFFSET), buttonContainer,
			upgradeDropImage);
}

WindowStateDroppableCreateSelect::~WindowStateDroppableCreateSelect() {
	delete (laserDropImage);
	delete (spreadDropImage);
	delete (missileDropImage);
	delete (bombDropImage);
	delete (upgradeDropImage);
	delete (buttonContainer);

	delete (laserDropButton);
	delete (missileDropButton);
	delete (spreadDropButton);
	delete (bombDropButton);
	delete (upgradeDropButton);
}

int WindowStateDroppableCreateSelect::update(double dt) {

	std::vector<std::string> returningArgs;

	laserDropButton->update();
	missileDropButton->update();
	spreadDropButton->update();
	upgradeDropButton->update();
	bombDropButton->update();

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	if (laserDropButton->isClicked()) {
		returningArgs.push_back("laser");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (missileDropButton->isClicked()) {
		returningArgs.push_back("missile");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (spreadDropButton->isClicked()) {
		returningArgs.push_back("spread");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}
	if (upgradeDropButton->isClicked()) {
		nextState = WindowState::STATEDROPPABLEUPGRADE;

		returnChanges = true;
	}
	if (bombDropButton->isClicked()) {
		returningArgs.push_back("bomb");
		argumentsToReturn.addLineArg(returningArgs);
		returnChanges = true;
	}

	return nextState;
}

void WindowStateDroppableCreateSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	laserDropButton->render(cameraX, cameraY);
	missileDropButton->render(cameraX, cameraY);
	spreadDropButton->render(cameraX, cameraY);
	upgradeDropButton->render(cameraX, cameraY);
	bombDropButton->render(cameraX, cameraY);
}

StateArgs WindowStateDroppableCreateSelect::unloadArguments() {
	return argumentsToReturn;
}

StateArgs WindowStateDroppableCreateSelect::passArguments() {
	std::vector<std::string> passingArguments;

	for (int i = 0; i < 2; i++) {
		passingArguments.push_back("");
	}

	return StateArgs(passingArguments);
}

void WindowStateDroppableCreateSelect::handleUnstack(StateArgs arguments) {
	argumentsToReturn = arguments;
}
