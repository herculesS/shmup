/*
 * WindowStatePatternSelect.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStatePatternSelect.h"

WindowStatePatternSelect::WindowStatePatternSelect(StateArgs arguments) :
		WindowState("Selecione o Pattern") {
	this->arguments = arguments;
	burstPatternImage = new Sprite("../gfx/burstPatternImage.png");
	spreadPatternImage = new Sprite("../gfx/spreadPatternImage.png");
	flowerPatternImage = new Sprite("../gfx/flowerPatternImage.png");
	buttonContainerImage = new Sprite("../gfx/buttonContainer.png");
	newPatternContainerImage = new Sprite("../gfx/invisibleSprite.png");
	newPatternImage = new Sprite("../gfx/newFile.png");
	deletePatternImage = new Sprite("../gfx/deleteImage.png");
	clickedButtonIndex = -1;
	creatingNewPattern = false;
	deletingPattern = false;

	newPatternButton = new Button(
			Point(NEW_PATTERN_BUTTON_X, NEW_PATTERN_BUTTON_Y),
			newPatternContainerImage, newPatternImage);
	deletePatternButton = new Button(
			Point(DELETE_PATTERN_BUTTON_X, DELETE_PATTERN_BUTTON_Y),
			newPatternContainerImage, deletePatternImage);

	for (int i = 0; i < arguments.getSize(); i++) {
		createNewButton(arguments.getArg(i, 1));
	}

}

WindowStatePatternSelect::~WindowStatePatternSelect() {
	delete (burstPatternImage);
	delete (spreadPatternImage);
	delete (flowerPatternImage);
	delete (buttonContainerImage);
	delete (newPatternContainerImage);
	delete (newPatternImage);
	delete (newPatternButton);
	delete (deletePatternImage);
	delete (deletePatternButton);

	for (std::vector<Button*>::iterator it = patternButtonVector.begin();
			it != patternButtonVector.end(); ++it) {
		delete (*it);
		it = patternButtonVector.erase(it);
		it--;
	}
}

int WindowStatePatternSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;
	creatingNewPattern = false;

	newPatternButton->update();
	deletePatternButton->update();

	for (unsigned int i = 0; i < patternButtonVector.size(); i++) {
		patternButtonVector[i]->update();
		if (patternButtonVector[i]->isClicked()) {
			if (deletingPattern) {
				deletePattern(i);
			} else {
				nextState = nextStateVector[i];
				clickedButtonIndex = i;
			}

		}
	}

	if (newPatternButton->isClicked()) {
		creatingNewPattern = true;
		nextState = WindowState::STATEPATTERNCREATESELECT;
	}
	if (deletePatternButton->isClicked()) {
		deletingPattern = !deletingPattern;
	}
	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;

}

void WindowStatePatternSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	newPatternButton->render(cameraX, cameraY);
	deletePatternButton->render(cameraX, cameraY);

	for (std::vector<Button*>::iterator it = patternButtonVector.begin();
			it != patternButtonVector.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}
}

StateArgs WindowStatePatternSelect::passArguments() {
	StateArgs argumentsToPass;

	if (!creatingNewPattern) {
		argumentsToPass.addLineArg(arguments.getLineArgs(clickedButtonIndex));
	}

	return argumentsToPass;
}

StateArgs WindowStatePatternSelect::unloadArguments() {
	return arguments;
}

void WindowStatePatternSelect::deletePattern(int index) {
	deletingPattern = false;

	arguments.eraseLineArg(index);

	for (unsigned int i = index; i < patternButtonVector.size() - 1; i++) {
		nextStateVector[i + 1] = nextStateVector[i];
	}

	patternButtonVector.erase(patternButtonVector.begin() + index);

	resetButtonsPosition();
}

void WindowStatePatternSelect::resetButtonsPosition() {
	for (unsigned int i = 0; i < patternButtonVector.size(); i++) {
		patternButtonVector[i]->setPosition(
				Point(
						PATTERN_BUTTONS_X
								+ ((i % NUM_BUTTONS_LINE)
										* PATTERN_BUTTONS_OFFSET),
						PATTERN_BUTTONS_Y
								+ ((i / NUM_BUTTONS_LINE)
										* PATTERN_BUTTONS_OFFSET)));
	}
}

void WindowStatePatternSelect::createNewButton(std::string patternName) {
	nextStateVector[patternButtonVector.size()] = selectButtonState(
			patternName);
	patternButtonVector.push_back(
			new Button(
					Point(
							PATTERN_BUTTONS_X
									+ ((patternButtonVector.size()
											% NUM_BUTTONS_LINE)
											* PATTERN_BUTTONS_OFFSET),
							PATTERN_BUTTONS_Y
									+ ((patternButtonVector.size()
											/ NUM_BUTTONS_LINE)
											* PATTERN_BUTTONS_OFFSET)),
					buttonContainerImage, selectPatternImage(patternName)));
}

void WindowStatePatternSelect::handleUnstack(StateArgs arguments) {
	if (creatingNewPattern) {
		if (!arguments.isEmpty()) {
			this->arguments.addLineArg(arguments.getLineArgs(0));
			createNewButton(arguments.getArg(1));
		}
	} else {
		this->arguments.setLineArgs(clickedButtonIndex,
				arguments.getLineArgs(0));
	}
}

Sprite* WindowStatePatternSelect::selectPatternImage(std::string patternName) {
	Sprite* toReturn;

	if (strcasecmp("flower", patternName.c_str()) == 0) {
		toReturn = flowerPatternImage;
	} else if (strcasecmp("spread", patternName.c_str()) == 0) {
		toReturn = spreadPatternImage;
	} else {
		toReturn = burstPatternImage;
	}

	return toReturn;
}

int WindowStatePatternSelect::selectButtonState(std::string patternName) {
	int toReturn;

	if (strcasecmp("flower", patternName.c_str()) == 0) {
		toReturn = WindowState::STATEPATTERNFLOWER;
	} else if (strcasecmp("spread", patternName.c_str()) == 0) {
		toReturn = WindowState::STATEPATTERNSPREAD;
	} else {
		toReturn = WindowState::STATEPATTERNBURST;
	}

	return toReturn;

}
