/*
 * MenuOption.h
 *
 *  Created on: Jun 14, 2013
 *      Author: AT WORK
 */

#ifndef MENUOPTION_H_
#define MENUOPTION_H_
#include "Sprite.h"
#include "Text.h"
#include "Rect.h"
#include "InputManager.h"

class MenuOption {
private:
	Text* OptionText;
	Sprite *OpSelectedSprite;
	bool Selected;
	bool Clicked;
	Rect box;
	SDL_Color highLight, TextColor;
	int OptionState;

public:
	MenuOption(Text*, int OptionState, Sprite* bg = NULL);
	Text* getText() {
		return OptionText;
	}
	bool isSelected();
	bool isClicked();
	void setSelected(bool selected);
	int getState() {
		return OptionState;
	}
	void render();
	int update();
	virtual ~MenuOption();
};
#endif /* MENUOPTION_H_ */
