/*
 * WindowState.cpp
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#include "WindowState.h"

WindowState::WindowState(std::string title) {

	SDL_Color color;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	this->title = new Text("../ttf/Arial-Black.ttf", title, 20, 0, color,
			TITLE_POSITION_X, TITLE_POSITION_Y);
	returnChanges = false;
	nextState = WindowState::STATENOCHANGE;
}

WindowState::~WindowState() {
	delete (title);
}

void WindowState::render(float cameraX, float cameraY) {
	title->render(cameraX, cameraY, true);
}

void WindowState::returnWithChanges() {
	returnChanges = true;
}
