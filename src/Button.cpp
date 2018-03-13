/*
 * Button.cpp
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#include "Button.h"

Button::Button(Point position, Sprite* buttonSprite,
		Sprite* buttonImageSprite) {
	this->buttonSprite = buttonSprite;
	this->buttonImageSprite = buttonImageSprite;
	this->position = position;
	this->clicked = false;

	buttonRect.x = position.getX() - buttonSprite->getWidth() / 2;
	buttonRect.y = position.getY() - buttonSprite->getHeight() / 2;
	buttonRect.w = buttonSprite->getWidth();
	buttonRect.h = buttonSprite->getHeight();
}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::update() {

	clicked = false;

	if (InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)
			&& InputManager::getInstance()->isMouseInside(&buttonRect)) {
		clicked = true;
	}
}

void Button::render(float cameraX, float cameraY) {
	buttonSprite->render(position.getX() - cameraX, position.getY() - cameraY,
			true);
	buttonImageSprite->render(position.getX() - cameraX,
			position.getY() - cameraY, true);
}
