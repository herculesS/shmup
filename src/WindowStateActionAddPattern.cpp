/*
 * WindowStateActionAddPattern.cpp
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#include "WindowStateActionAddPattern.h"

WindowStateActionAddPattern::WindowStateActionAddPattern(StateArgs arguments) :
		WindowState("Acao Adicionar Pattern") {
	this->arguments = arguments;
	burstPatternImage = new Sprite("../gfx/burstPatternImage.png");
	spreadPatternImage = new Sprite("../gfx/spreadPatternImage.png");
	flowerPatternImage = new Sprite("../gfx/flowerPatternImage.png");
	buttonContainerImage = new Sprite("../gfx/buttonContainer.png");

	Sprite* buttonImage;

	if (strcasecmp("flower", arguments.getArg(1).c_str()) == 0) {
		buttonImage = flowerPatternImage;
		nextPatternState = WindowState::STATEPATTERNFLOWER;
	} else if (strcasecmp("spread", arguments.getArg(1).c_str()) == 0) {
		buttonImage = spreadPatternImage;
		nextPatternState = WindowState::STATEPATTERNSPREAD;
	} else {
		buttonImage = burstPatternImage;
		nextPatternState = WindowState::STATEPATTERNBURST;
	}

	patternButton = new Button(Point(PATTERN_BUTTON_X, PATTERN_BUTTON_Y),
			buttonContainerImage, buttonImage);

}

WindowStateActionAddPattern::~WindowStateActionAddPattern() {
	delete (burstPatternImage);
	delete (flowerPatternImage);
	delete (spreadPatternImage);
	delete (buttonContainerImage);
	delete (patternButton);
}

int WindowStateActionAddPattern::update(double dt) {

	patternButton->update();

	nextState = WindowState::STATENOCHANGE;

	if (patternButton->isClicked()) {
		nextState = nextPatternState;
	}
	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;

}

void WindowStateActionAddPattern::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	patternButton->render(cameraX, cameraY);
}

StateArgs WindowStateActionAddPattern::passArguments() {
	std::vector<std::string> argumentsToPass;

	argumentsToPass.push_back("pattern");
	argumentsToPass.push_back(arguments.getArg(1));
	argumentsToPass.push_back(arguments.getArg(2));
	argumentsToPass.push_back(arguments.getArg(3));
	argumentsToPass.push_back(arguments.getArg(4));
	argumentsToPass.push_back(arguments.getArg(5));
	argumentsToPass.push_back(arguments.getArg(6));
	argumentsToPass.push_back(arguments.getArg(7));

	if (strcasecmp(arguments.getArg(1).c_str(), "flower") == 0) {
		argumentsToPass.push_back(arguments.getArg(8));
		argumentsToPass.push_back(arguments.getArg(9));
	} else if (strcasecmp(arguments.getArg(1).c_str(), "spread") == 0) {
		argumentsToPass.push_back(arguments.getArg(8));
	}

	return StateArgs(argumentsToPass);
}

void WindowStateActionAddPattern::handleUnstack(StateArgs arguments) {
	arguments.setArg(0, "add");

	this->arguments = arguments;
}

StateArgs WindowStateActionAddPattern::unloadArguments() {
	return arguments;
}
