/*
 * StateMenu.h
 *
 *  Created on: Jun 13, 2013
 *      Author: AT WORK
 */

#ifndef STATEMENU_H_
#define STATEMENU_H_

#include "State.h"
#include "Text.h"
#include "Sprite.h"
#include "SDLBase.h"
#include "InputManager.h"
//#include "Audio.h"
#include "Menu.h"

class StateMenu: public State {
private:
	Sprite* Bg;
	Sprite* MenuBg;
	Sprite* menuSelectorSprite;
	Menu* menu;
	bool quitGame;

public:
	StateMenu();
	void load(StateArgs arguments);
	void input();
	int update(double dt);
	void render();
	StateArgs unload();
	virtual ~StateMenu();
};

#endif /* STATEMENU_H_ */
