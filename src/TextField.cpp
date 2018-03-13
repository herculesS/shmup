/*
 * TextField.cpp
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#include "TextField.h"

TextField::TextField(Point position, std::string initialText) {
	this->position = position;
	this->inputString = initialText;
	this->active = false;
	this->highlighted = false;
	containerSprite = new Sprite("../gfx/textContainerTeste.png");

	this->containerBox.x = position.getX() - containerSprite->getWidth() / 2;
	this->containerBox.y = position.getY() - containerSprite->getHeight() / 2;
	this->containerBox.w = containerSprite->getWidth();
	this->containerBox.h = containerSprite->getHeight();

	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	textToDisplay = new Text("../ttf/Arial-Black.ttf", initialText, 12, 0,
			color, position.getX(), position.getY());
	highlightSprite = new Sprite("../gfx/textContainerHighlighter.png");
}

TextField::~TextField() {
	delete (textToDisplay);
	delete (containerSprite);
	delete (highlightSprite);
}

void TextField::update() {

	highlightSprite->setHidden(true);
	highlighted = false;

	if (InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)) {
		if (InputManager::getInstance()->isMouseInside(&containerBox)) {
			active = true;
		} else {
			active = false;
		}
	}

	if (InputManager::getInstance()->isMouseInside(&containerBox)) {
		highlighted = true;
	}

	if (active) {
		highlighted = true;
		std::string temp = inputString;

		if (inputString.length() <= 10) {
			int pressedKey = InputManager::getInstance()->getDownKey(SDLK_0,
					SDLK_9);

			// Se um número foi apertado, simplesmente adicionamos
			// Senão, vemos se o Backspace foi apertado e apagamos o último caracter
			// se existir.
			if (pressedKey != -1) {
				inputString += (char) pressedKey;
			}
		}

		if (InputManager::getInstance()->isKeyDown(SDLK_BACKSPACE)
				&& inputString.length() != 0) {
			inputString.erase(inputString.length() - 1);
		}
		if (InputManager::getInstance()->isKeyDown(SDLK_MINUS)
				&& inputString.empty()) {
			inputString += (char) SDLK_MINUS;
		}
		if (InputManager::getInstance()->isKeyDown(SDLK_RETURN)) {
			active = false;
		}

		// Se houve mudança na string, ela deve ser atualizada
		if (temp != inputString) {
			textToDisplay->setText(inputString);
		}
	}

	if (highlighted) {
		highlightSprite->setHidden(false);
	}

}

void TextField::render(float cameraX, float cameraY) {
	highlightSprite->render(position.getX() - cameraX,
			position.getY() - cameraY, true);
	containerSprite->render(position.getX() - cameraX,
			position.getY() - cameraY, true);
	textToDisplay->render(cameraX, cameraY, true);
}
