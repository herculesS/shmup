/*
 * WindowStateOrbitSelect.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "WindowStateOrbitSelect.h"

WindowStateOrbitSelect::WindowStateOrbitSelect(StateArgs arguments) :
		WindowState("Selecione a orbita") {
	this->arguments = arguments;

	deleteOrbitImage = new Sprite("../gfx/deleteImage.png");
	deleteOrbitContainer = new Sprite("../gfx/invisibleSprite.png");
	buttonContainer = new Sprite("../gfx/buttonContainer.png");
	orbitButtonImage = new Sprite("../gfx/orbitsImage.png");

	deletingOrbit = false;
	clickedButtonIndex = -1;

	deleteOrbitButton = new Button(
			Point(DELETE_ORBIT_BUTTON_X, DELETE_ORBIT_BUTTON_Y),
			deleteOrbitContainer, deleteOrbitImage);

	for (int i = 0; i < arguments.getSize(); i++) {
		createNewButton();
	}
}

WindowStateOrbitSelect::~WindowStateOrbitSelect() {
	delete (buttonContainer);
	delete (orbitButtonImage);
	delete (deleteOrbitButton);
	delete (deleteOrbitImage);
	delete (deleteOrbitContainer);

	for (std::vector<Button*>::iterator it = orbitButtonVector.begin();
			it != orbitButtonVector.end(); ++it) {
		delete (*it);
		it = orbitButtonVector.erase(it);
		it--;
	}
}

int WindowStateOrbitSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;

	deleteOrbitButton->update();

	for (unsigned int i = 0; i < orbitButtonVector.size(); i++) {
		orbitButtonVector[i]->update();
		if (orbitButtonVector[i]->isClicked()) {
			if (deletingOrbit) {
				deleteOrbit(i);
			} else {
				nextState = WindowState::STATEORBIT;
				clickedButtonIndex = i;
			}
		}
	}

	if (deleteOrbitButton->isClicked()) {
		deletingOrbit = !deletingOrbit;
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateOrbitSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	deleteOrbitButton->render(cameraX, cameraY);

	for (unsigned int i = 0; i < orbitButtonVector.size(); i++) {
		orbitButtonVector[i]->render(cameraX, cameraY);
	}
}

StateArgs WindowStateOrbitSelect::unloadArguments() {
	return arguments;
}

StateArgs WindowStateOrbitSelect::passArguments() {
	return StateArgs(arguments.getLineArgs(clickedButtonIndex));
}

void WindowStateOrbitSelect::handleUnstack(StateArgs arguments) {
	this->arguments.setLineArgs(clickedButtonIndex, arguments.getLineArgs(0));
}

void WindowStateOrbitSelect::deleteOrbit(int index) {
	deletingOrbit = false;

	arguments.eraseLineArg(index);

	orbitButtonVector.erase(orbitButtonVector.begin() + index);

	resetButtonsPosition();
}

void WindowStateOrbitSelect::resetButtonsPosition() {
	for (unsigned int i = 0; i < orbitButtonVector.size(); i++) {
		orbitButtonVector[i]->setPosition(
				Point(
						ORBIT_BUTTONS_X
								+ ((i % NUM_ORBITS_LINE) * ORBIT_BUTTONS_OFFSET),
						ORBIT_BUTTONS_Y
								+ ((i / NUM_ORBITS_LINE) * ORBIT_BUTTONS_OFFSET)));
	}
}

void WindowStateOrbitSelect::createNewButton() {
	orbitButtonVector.push_back(
			new Button(
					Point(
							ORBIT_BUTTONS_X
									+ ((orbitButtonVector.size()
											% NUM_ORBITS_LINE)
											* ORBIT_BUTTONS_OFFSET),
							ORBIT_BUTTONS_Y
									+ ((orbitButtonVector.size()
											/ NUM_ORBITS_LINE)
											* ORBIT_BUTTONS_OFFSET)),
					buttonContainer, orbitButtonImage));
}
