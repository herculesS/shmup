/*
 * StateMenu.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: AT WORK
 */

#include "StateMenu.h"

StateMenu::StateMenu() {
}
void StateMenu::input() {
	if (InputManager::getInstance()->QuitGame())
		quitGame = true;
}
void StateMenu::load(StateArgs arguments) {
	Bg = new Sprite("../gfx/Inicio.png");
	MenuBg = new Sprite("../gfx/MenuBg.jpg");
	menuSelectorSprite = new Sprite("../gfx/Selector.png");
	menu = new Menu(400, 400, NULL);

	quitGame = false;
	nextState = SDLBase::STATENOCHANGE;
}
int StateMenu::update(double dt) {

	nextState = menu->update();

	if (quitGame)
		nextState = SDLBase::STATEQUIT;

	return nextState;
}
void StateMenu::render() {
	Bg->render(0, 0, 0);
	menu->render();
}
StateArgs StateMenu::unload() {
	delete (Bg);
	delete (MenuBg);
	delete (menu);
	delete (menuSelectorSprite);
	return StateArgs();
}
StateMenu::~StateMenu() {
}

