/*
 * Menu.h
 *
 *  Created on: Jun 14, 2013
 *      Author: AT WORK
 */

#ifndef MENU_H_
#define MENU_H_

#define MENU_HEIGHT_DIFF 10

#include "Sprite.h"
#include "Text.h"
#include "Rect.h"
#include "InputManager.h"
#include "MenuOption.h"
#include <vector>

class Menu {
private:
	Sprite* bg;
	std::vector<MenuOption*> *options;
	std::vector<MenuOption*>::iterator opcaoAtual;
	Rect box;
	SDL_Color textColor, highLight;
	Sprite* menuSelectorSprite;

	Text* playText;
	Text* optionsText;
	Text* quitText;

public:
	Menu(float x, float y, Sprite* bg = NULL);
	void render();
	int update();
	virtual ~Menu();
};

#endif /* MENU_H_ */
