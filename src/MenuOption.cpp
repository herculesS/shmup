/*
 * MenuOption.cpp
 *
 *  Created on: Jun 16, 2013
 *      Author: AT WORK
 */

#include "MenuOption.h"

MenuOption::MenuOption(Text* OptionText, int OptionState,
		Sprite* OpSelectedSprite) {
	// TODO Auto-generated constructor stub
	this->OpSelectedSprite = OpSelectedSprite;
	this->OptionText = OptionText;
	this->OptionState = OptionState;

	Selected = false;
	Clicked = false;
	TextColor = (SDL_Color ) { 77, 77, 77 };
	highLight = (SDL_Color ) { 255, 255, 255 };
}

bool MenuOption::isSelected() {
	return Selected;
}
bool MenuOption::isClicked() {
	return Clicked;
}
void MenuOption::setSelected(bool selected) {
	Selected = selected;
}
MenuOption::~MenuOption() {
}
int MenuOption::update() {
	SDL_Rect textBox;
	textBox.x = OptionText->getPos()->getX() - OptionText->getWidth() / 2;
	textBox.y = OptionText->getPos()->getY() - OptionText->getHeight() / 2;
	textBox.w = OptionText->getWidth();
	textBox.h = OptionText->getHeight();

	Clicked = false;

	if (InputManager::getInstance()->isMouseInside(&textBox)) {
		OptionText->setColor(highLight);
		Selected = true;
	}
	if (Selected
			&& (InputManager::getInstance()->isMouseDown(SDL_BUTTON_LEFT)
					|| InputManager::getInstance()->isKeyDown(SDLK_RETURN))) {
		Clicked = true;
	}
	return 0;
}
void MenuOption::render() {
	if (this->OpSelectedSprite != NULL && (Selected)) {
		this->OpSelectedSprite->render(
				OptionText->getPos()->getX() - OptionText->getWidth() / 2
						- OpSelectedSprite->getWidth(),
				OptionText->getPos()->getY()
						- OpSelectedSprite->getHeight() / 2, 0);
	}
	this->OptionText->render(0, 0, 1);
}

