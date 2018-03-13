/*
 * Menu.cpp
 *
 *  Created on: Jun 14, 2013
 *      Author: AT WORK
 */

#include "Menu.h"

Menu::Menu(float x, float y, Sprite* bg) {
	box.setX(x);
	box.setY(y);
	highLight = (SDL_Color ) { 255, 255, 255 };
	textColor = (SDL_Color ) { 77, 77, 77 };
	menuSelectorSprite = new Sprite("../gfx/Selector.png");

	playText = new Text("../ttf/Helvetica LT Black.ttf", "START GAME", 20, 0,
			highLight, 0, 0);
	optionsText = new Text("../ttf/Helvetica LT Black.ttf", "LEVEL EDITOR", 20,
			0, textColor, 0, 0);
	quitText = new Text("../ttf/Helvetica LT Black.ttf", "QUIT", 20, 0,
			textColor, 0, 0);

	options = new std::vector<MenuOption*>;
	options->push_back(new MenuOption(playText, SDLBase::STATEGAME, NULL));
	options->push_back(new MenuOption(optionsText, SDLBase::STATEEDITOR, NULL));
	options->push_back(new MenuOption(quitText, SDLBase::STATEQUIT, NULL));

	opcaoAtual = options->begin();
	(*opcaoAtual)->setSelected(true);

	this->bg = bg;
	if (bg == NULL) {
		float height = 0.0, width = 0.0;
		height = y;

		for (std::vector<MenuOption*>::iterator it = options->begin();
				it != options->end(); ++it) {
			if ((*it)->getText()->getWidth() > width) {
				width = (*it)->getText()->getWidth();
			}
			height += (*it)->getText()->getHeight() + MENU_HEIGHT_DIFF;
			(*it)->getText()->setPos(x, height);
		}

		box.setH(width);
		box.setH(height);

	} else {
		box.setW(bg->getWidth());
		box.setH(bg->getHeight());
		float height = box.getY() - box.getH() / 2
				+ options->at(0)->getText()->getHeight() / 2;
		for (std::vector<MenuOption*>::iterator it = options->begin();
				it != options->end(); ++it) {
			(*it)->getText()->setPos(x, height);
			height += box.getH() / (options->size());
		}
	}
}
void Menu::render() {
	if (bg != NULL) {
		bg->render(box.getCenterRef()->getX(), box.getCenterRef()->getY(), 1);
	}
	for (std::vector<MenuOption*>::iterator it = options->begin();
			it != options->end(); ++it) {
		(*it)->render();
	}
}
int Menu::update() {
	for (std::vector<MenuOption*>::iterator it = options->begin();
			it != options->end(); ++it) {
		(*it)->update();
		if ((*it)->isSelected()) {
			if (opcaoAtual != it) {
				(*opcaoAtual)->getText()->setColor(textColor);
				(*opcaoAtual)->setSelected(false);
				opcaoAtual = it;
			}
		}
		if ((*it)->isClicked()) {
			return (*it)->getState();
		}
	}
	if (InputManager::getInstance()->isKeyDown(SDLK_DOWN)) {
		(*opcaoAtual)->getText()->setColor(textColor);
		(*opcaoAtual)->setSelected(false);
		if (opcaoAtual < options->end() - 1) {
			++opcaoAtual;
		} else {
			opcaoAtual = options->begin();
		}
		(*opcaoAtual)->getText()->setColor(highLight);
		(*opcaoAtual)->setSelected(true);
	}
	if (InputManager::getInstance()->isKeyDown(SDLK_UP)) {
		(*opcaoAtual)->getText()->setColor(textColor);
		(*opcaoAtual)->setSelected(false);
		if (opcaoAtual > options->begin()) {
			--opcaoAtual;
		} else {
			opcaoAtual = options->end() - 1;
		}
		(*opcaoAtual)->getText()->setColor(highLight);
		(*opcaoAtual)->setSelected(true);
	}
	return SDLBase::STATENOCHANGE;
}
Menu::~Menu() {
	delete (menuSelectorSprite);
	delete (playText);
	delete (optionsText);
	delete (quitText);
	for (std::vector<MenuOption*>::iterator it = options->begin();
			it != options->end(); ++it) {
		delete (*it);
		it = options->erase(it);
		it--;
	}
	delete (options);
}

