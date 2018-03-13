/*
 * WindowStateDroppableSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateDroppableSelect.h"

WindowStateDroppableSelect::WindowStateDroppableSelect(StateArgs arguments) :
		WindowState("Selecione os drops") {
	this->arguments = arguments;
	laserDropImage = new Sprite("../gfx/laserDropImage.png");
	spreadDropImage = new Sprite("../gfx/spreadDropImage.png");
	missileDropImage = new Sprite("../gfx/missileDropImage.png");
	bombDropImage = new Sprite("../gfx/bombDropImage.png");
	upgradeDropImage = new Sprite("../gfx/upgradeDropImage.png");
	buttonContainer = new Sprite("../gfx/buttonContainer.png");
	newDropImage = new Sprite("../gfx/newFile.png");
	newDropContainer = new Sprite("../gfx/invisibleSprite.png");
	deleteDropImage = new Sprite("../gfx/deleteImage.png");

	clickedButtonIndex = -1;
	creatingNewDrop = false;
	deletingDrop = false;

	newDropButton = new Button(Point(NEW_DROP_X, NEW_DROP_Y), newDropContainer,
			newDropImage);
	deleteDropButton = new Button(
			Point(DELETE_DROP_BUTTON_X, DELETE_DROP_BUTTON_Y), newDropContainer,
			deleteDropImage);

	for (int i = 0; i < arguments.getSize(); i++) {
		createNewButton(arguments.getArg(i, 0));
	}
}

WindowStateDroppableSelect::~WindowStateDroppableSelect() {
	delete (laserDropImage);
	delete (spreadDropImage);
	delete (missileDropImage);
	delete (bombDropImage);
	delete (upgradeDropImage);
	delete (buttonContainer);
	delete (newDropContainer);
	delete (newDropButton);
	delete (newDropImage);
	delete (deleteDropButton);
	delete (deleteDropImage);

	for (std::vector<Button*>::iterator it = dropButtonVector.begin();
			it != dropButtonVector.end(); ++it) {
		delete (*it);
		it = dropButtonVector.erase(it);
		it--;
	}
}

int WindowStateDroppableSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;
	creatingNewDrop = false;

	for (unsigned int i = 0; i < dropButtonVector.size(); i++) {
		dropButtonVector[i]->update();
		if (dropButtonVector[i]->isClicked()) {
			if (deletingDrop) {
				deleteDrop(i);
			} else {
				nextState = nextStateVector[i];
				clickedButtonIndex = i;
			}
		}
	}

	newDropButton->update();
	deleteDropButton->update();

	if (newDropButton->isClicked()) {
		nextState = WindowState::STATEDROPPABLECREATESELECT;
		creatingNewDrop = true;
	}

	if (deleteDropButton->isClicked()) {
		deletingDrop = !deletingDrop;
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateDroppableSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	newDropButton->render(cameraX, cameraY);
	deleteDropButton->render(cameraX, cameraY);

	for (std::vector<Button*>::iterator it = dropButtonVector.begin();
			it != dropButtonVector.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}

}

StateArgs WindowStateDroppableSelect::passArguments() {
	if (creatingNewDrop) {
		return StateArgs();
	}

	return StateArgs(arguments.getLineArgs(clickedButtonIndex));
}

StateArgs WindowStateDroppableSelect::unloadArguments() {
	return arguments;
}

void WindowStateDroppableSelect::handleUnstack(StateArgs arguments) {
	if (creatingNewDrop) {
		if (!arguments.isEmpty()) {
			this->arguments.addLineArg(arguments.getLineArgs(0));
			createNewButton(arguments.getArg(0));
		}
	} else {
		this->arguments.setLineArgs(clickedButtonIndex,
				arguments.getLineArgs(0));
	}
}

void WindowStateDroppableSelect::deleteDrop(int index) {
	deletingDrop = false;

	arguments.eraseLineArg(index);

	for (unsigned int i = index; i < dropButtonVector.size() - 1; i++) {
		nextStateVector[i + 1] = nextStateVector[i];
	}

	dropButtonVector.erase(dropButtonVector.begin() + index);

	resetButtonsPosition();
}

void WindowStateDroppableSelect::resetButtonsPosition() {
	for (unsigned int i = 0; i < dropButtonVector.size(); i++) {
		dropButtonVector[i]->setPosition(
				Point(DROPS_BASE_X + ((i % NUM_DROPS_LINE) * DROPS_OFFSET),
						DROPS_BASE_Y + ((i / NUM_DROPS_LINE) * DROPS_OFFSET)));
	}
}

void WindowStateDroppableSelect::createNewButton(std::string dropName) {
	nextStateVector[dropButtonVector.size()] = selectButtonState(dropName);
	dropButtonVector.push_back(
			new Button(
					Point(
							DROPS_BASE_X
									+ ((dropButtonVector.size() % NUM_DROPS_LINE)
											* DROPS_OFFSET),
							DROPS_BASE_Y
									+ ((dropButtonVector.size() / NUM_DROPS_LINE)
											* DROPS_OFFSET)), buttonContainer,
					selectDropImage(dropName)));
}

Sprite* WindowStateDroppableSelect::selectDropImage(std::string dropName) {
	Sprite* toReturn;

	if (strcasecmp(dropName.c_str(), "laser") == 0) {
		toReturn = laserDropImage;
	} else if (strcasecmp(dropName.c_str(), "missile") == 0) {
		toReturn = missileDropImage;
	} else if (strcasecmp(dropName.c_str(), "spread") == 0) {
		toReturn = spreadDropImage;
	} else if (strcasecmp(dropName.c_str(), "upgrade") == 0) {
		toReturn = upgradeDropImage;
	} else {
		toReturn = bombDropImage;
	}

	return toReturn;
}

int WindowStateDroppableSelect::selectButtonState(std::string dropName) {
	int toReturn;

	if (strcasecmp(dropName.c_str(), "laser") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(dropName.c_str(), "missile") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(dropName.c_str(), "spread") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(dropName.c_str(), "upgrade") == 0) {
		toReturn = WindowState::STATEDROPPABLEUPGRADE;
	} else {
		toReturn = WindowState::STATENOCHANGE;
	}

	return toReturn;
}
