/*
 * WindowStateActionSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateActionSelect.h"

WindowStateActionSelect::WindowStateActionSelect(StateArgs arguments) :
		WindowState("Selecione a acao") {
	this->arguments = arguments;
	dieActionImage = new Sprite("../gfx/dieActionImage.png");
	moveActionImage = new Sprite("../gfx/moveActionImage.png");
	moveStraightActionImage = new Sprite("../gfx/moveStraightActionImage.png");
	addPatternActionImage = new Sprite("../gfx/addPatternActionImage.png");
	shootImage = new Sprite("../gfx/shootImage.png");
	stopShootingImage = new Sprite("../gfx/stopShootingImage.png");
	waitActionImage = new Sprite("../gfx/waitActionImage.png");
	addOrbitActionImage = new Sprite("../gfx/addOrbitsImage.png");
	buttonContainerImage = new Sprite("../gfx/buttonContainer.png");
	newActionImage = new Sprite("../gfx/newFile.png");
	deleteActionImage = new Sprite("../gfx/deleteImage.png");
	swapButtonImage = new Sprite("../gfx/swapImage.jpg");
	swapButtonContainer = new Sprite("../gfx/invisibleSprite.png");
	clickedButtonIndex = -1;
	swapCounter = 0;
	creatingNewAction = false;
	deletingAction = false;
	swapping = false;

	newActionButton = new Button(Point(NEW_ACTION_X, NEW_ACTION_Y),
			newActionImage, swapButtonContainer);
	deleteActionButton = new Button(
			Point(DELETE_ACTION_BUTTON_X, DELETE_ACTION_BUTTON_Y),
			deleteActionImage, swapButtonContainer);
	swapButton = new Button(Point(SWAP_BUTTON_X, SWAP_BUTTON_Y),
			swapButtonImage, swapButtonContainer);

	for (int i = 0; i < arguments.getSize(); i++) {
		createNewButton(arguments.getArg(i, 0));
	}
}

WindowStateActionSelect::~WindowStateActionSelect() {
	delete (dieActionImage);
	delete (moveActionImage);
	delete (moveStraightActionImage);
	delete (addPatternActionImage);
	delete (shootImage);
	delete (stopShootingImage);
	delete (waitActionImage);
	delete (addOrbitActionImage);
	delete (buttonContainerImage);
	delete (swapButtonContainer);
	delete (swapButtonImage);
	delete (swapButton);
	delete (newActionImage);
	delete (newActionButton);
	delete (deleteActionImage);
	delete (deleteActionButton);

	for (std::vector<Button*>::iterator it = actionButtonVector.begin();
			it != actionButtonVector.end(); ++it) {
		delete (*it);
		it = actionButtonVector.erase(it);
		it--;
	}
}

int WindowStateActionSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;
	creatingNewAction = false;

	swapButton->update();
	newActionButton->update();
	deleteActionButton->update();

	for (unsigned int i = 0; i < actionButtonVector.size(); i++) {
		actionButtonVector[i]->update();
		if (actionButtonVector[i]->isClicked()) {
			if (swapping) {
				actionIndexes[swapCounter] = i;
				swapCounter++;
			} else if (deletingAction) {
				deleteAction(i);
			} else {
				nextState = nextStateVector[i];
				clickedButtonIndex = i;
			}
		}
	}

	if (swapButton->isClicked()) {
		if (swapping && swapCounter == 0) {
			swapping = false;
		} else {
			swapping = true;
		}
	}

	if (newActionButton->isClicked()) {
		nextState = WindowState::STATEACTIONCREATESELECT;
		creatingNewAction = true;
	}
	if (deleteActionButton->isClicked()) {
		deletingAction = !deletingAction;
	}

	if (swapCounter == 2) {
		swapActions(actionIndexes[0], actionIndexes[1]);
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;

}

void WindowStateActionSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	swapButton->render(cameraX, cameraY);
	newActionButton->render(cameraX, cameraY);
	deleteActionButton->render(cameraX, cameraY);
	for (std::vector<Button*>::iterator it = actionButtonVector.begin();
			it != actionButtonVector.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}
}

StateArgs WindowStateActionSelect::passArguments() {
	if (creatingNewAction) {
		return StateArgs();
	}
	return StateArgs(arguments.getLineArgs(clickedButtonIndex));
}

StateArgs WindowStateActionSelect::unloadArguments() {
	return arguments;
}

void WindowStateActionSelect::handleUnstack(StateArgs arguments) {
	if (creatingNewAction) {
		if (!arguments.isEmpty()) {
			this->arguments.addLineArg(arguments.getLineArgs(0));
			createNewButton(arguments.getArg(0));
		}
	} else {
		this->arguments.setLineArgs(clickedButtonIndex,
				arguments.getLineArgs(0));
	}
}

void WindowStateActionSelect::swapActions(int firstIndex, int secondIndex) {
	arguments.swapLines(firstIndex, secondIndex);

	Point aux;
	aux = actionButtonVector[firstIndex]->getPosition();
	actionButtonVector[firstIndex]->setPosition(
			actionButtonVector[secondIndex]->getPosition());
	actionButtonVector[secondIndex]->setPosition(aux);

	std::swap(actionButtonVector[firstIndex], actionButtonVector[secondIndex]);

	std::swap(nextStateVector[firstIndex], nextStateVector[secondIndex]);

	swapping = false;
	swapCounter = 0;
}

void WindowStateActionSelect::deleteAction(int index) {
	deletingAction = false;

	arguments.eraseLineArg(index);

	for (unsigned int i = index; i < actionButtonVector.size() - 1; i++) {
		nextStateVector[i + 1] = nextStateVector[i];
	}

	actionButtonVector.erase(actionButtonVector.begin() + index);

	resetButtonsPosition();
}

void WindowStateActionSelect::resetButtonsPosition() {
	for (unsigned int i = 0; i < actionButtonVector.size(); i++) {
		actionButtonVector[i]->setPosition(
				Point(
						ACTION_BUTTONS_X
								+ ((i % NUM_ACTIONS_LINE)
										* ACTION_BUTTONS_OFFSET),
						ACTION_BUTTONS_Y
								+ ((i / NUM_ACTIONS_LINE)
										* ACTION_BUTTONS_OFFSET)));
	}
}

void WindowStateActionSelect::createNewButton(std::string actionName) {
	nextStateVector[actionButtonVector.size()] = selectButtonState(actionName);
	actionButtonVector.push_back(
			new Button(
					Point(
							ACTION_BUTTONS_X
									+ ((actionButtonVector.size()
											% NUM_ACTIONS_LINE)
											* ACTION_BUTTONS_OFFSET),
							ACTION_BUTTONS_Y
									+ ((actionButtonVector.size()
											/ NUM_ACTIONS_LINE)
											* ACTION_BUTTONS_OFFSET)),
					buttonContainerImage, selectActionImage(actionName)));
}

Sprite* WindowStateActionSelect::selectActionImage(std::string actionName) {
	Sprite* toReturn = NULL;

	if (strcasecmp(actionName.c_str(), "die") == 0) {
		toReturn = dieActionImage;
	} else if (strcasecmp(actionName.c_str(), "move") == 0) {
		toReturn = moveActionImage;
	} else if (strcasecmp(actionName.c_str(), "movestraight") == 0) {
		toReturn = moveStraightActionImage;
	} else if (strcasecmp(actionName.c_str(), "add") == 0) {
		toReturn = addPatternActionImage;
	} else if (strcasecmp(actionName.c_str(), "shoot") == 0) {
		toReturn = shootImage;
	} else if (strcasecmp(actionName.c_str(), "stopshooting") == 0) {
		toReturn = stopShootingImage;
	} else if (strcasecmp(actionName.c_str(), "wait") == 0) {
		toReturn = waitActionImage;
	} else if (strcasecmp(actionName.c_str(), "orbit") == 0) {
		toReturn = addOrbitActionImage;
	} else {
		fprintf(stderr, "Acao nao reconhecida: %s.\n", actionName.c_str());
		exit(1);
	}

	return toReturn;
}

int WindowStateActionSelect::selectButtonState(std::string actionName) {
	int toReturn = -1;

	if (strcasecmp(actionName.c_str(), "die") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(actionName.c_str(), "move") == 0) {
		toReturn = WindowState::STATEACTIONMOVE;
	} else if (strcasecmp(actionName.c_str(), "movestraight") == 0) {
		toReturn = WindowState::STATEACTIONMOVESTRAIGHT;
	} else if (strcasecmp(actionName.c_str(), "add") == 0) {
		toReturn = WindowState::STATEACTIONADDPATTERN;
	} else if (strcasecmp(actionName.c_str(), "shoot") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(actionName.c_str(), "stopshooting") == 0) {
		toReturn = WindowState::STATENOCHANGE;
	} else if (strcasecmp(actionName.c_str(), "wait") == 0) {
		toReturn = WindowState::STATEACTIONWAIT;
	} else if (strcasecmp(actionName.c_str(), "orbit") == 0) {
		toReturn = WindowState::STATEORBIT;
	} else {
		fprintf(stderr, "Acao nao reconhecida: %s.\n", actionName.c_str());
		exit(1);
	}

	return toReturn;

}
