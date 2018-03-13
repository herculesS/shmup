/*
 * Checkbox.cpp
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#include "Checkbox.h"

Checkbox::Checkbox(Point position, bool selected) {
	this->position = position;
	this->selected = selected;
	selectedSprite = new Sprite("../gfx/checkBoxSelector.png");
	checkBoxContainerSprite = new Sprite("../gfx/checkBoxContainer.png");

	containerBox.x = position.getX() - checkBoxContainerSprite->getWidth() / 2;
	containerBox.y = position.getY() - checkBoxContainerSprite->getHeight() / 2;
	containerBox.w = checkBoxContainerSprite->getWidth();
	containerBox.h = checkBoxContainerSprite->getHeight();
}

Checkbox::~Checkbox() {
	delete (selectedSprite);
	delete (checkBoxContainerSprite);
}

void Checkbox::update() {
	if (InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)) {
		if (InputManager::getInstance()->isMouseInside(&containerBox)) {
			selected = !selected;
		}
	}

	if (selected) {
		selectedSprite->setHidden(false);
	} else {
		selectedSprite->setHidden(true);
	}
}

void Checkbox::render(float cameraX, float cameraY) {
	checkBoxContainerSprite->render(position.getX() - cameraX,
			position.getY() - cameraY, true);
	selectedSprite->render(position.getX() - cameraX, position.getY() - cameraY,
			true);
}
