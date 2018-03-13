/*
 * InputManager.cpp
 *
 *  Created on: 14/05/2013
 *      Author: vitor
 */

#include "InputManager.h"

InputManager* InputManager::instance = NULL;

InputManager::InputManager() {
	this->quitGame = false;
	this->mouseX = 0;
	this->mouseY = 0;
	this->mouse = 0;
	this->teclado = NULL;
}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}

void InputManager::initMouse() {

	int i;

	for (i = 0; i < N_MOUSE_BUTTONS; i++) {
		mouseButtonsDown[i] = 0;
		mouseButtonsUp[i] = 0;
	}
}

void InputManager::initKeyboard() {

	int i;

	for (i = 0; i < N_KEYS; i++) {
		keyDown[i] = 0;
		keyUp[i] = 0;
	}

}

void InputManager::update() {

	SDL_Event event;

	initMouse();
	initKeyboard();

	mouse = SDL_GetMouseState(&mouseX, &mouseY);
	teclado = SDL_GetKeyState(NULL);

	while (SDL_PollEvent(&event)) {
		/* verifica tipo do evento e toma a ação */
		switch (event.type) {
		case SDL_QUIT:
			quitGame = true;
			break;
		case SDL_KEYDOWN:
			keyDown[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyUp[event.key.keysym.sym] = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonsDown[event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonsUp[event.button.button] = true;
			break;
		default:
			break;
		}
	}

}

bool InputManager::isKeyDown(int key) {
	return keyDown[key];
}

int InputManager::getDownKey(int intervalStart, int intervalEnd) {

	for (int i = intervalStart; i <= intervalEnd; i++) {
		if (isKeyDown(i)) {
			return i;
		}
	}

	return -1;

}

bool InputManager::isKeyUp(int key) {
	return keyUp[key];
}

bool InputManager::isMouseDown(int button) {
	return mouseButtonsDown[button];
}

bool InputManager::isMouseUp(int button) {
	return mouseButtonsUp[button];
}

bool InputManager::isKeyPressed(int key) {
	return teclado[key];
}

bool InputManager::isMousePressed(int button) {
	return mouse & button;
}

int InputManager::mousePosX() {
	return mouseX;
}

int InputManager::mousePosY() {
	return mouseY;
}

bool InputManager::QuitGame() {
	return quitGame;
}

bool InputManager::isMouseInside(SDL_Rect* rect) {
	return mouseX > rect->x && mouseX < (rect->x + rect->w) && mouseY > rect->y
			&& mouseY < (rect->y + rect->h);
}
