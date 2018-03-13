/*
 * WindowStateDroppableCreateSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEDROPPABLECREATESELECT_H_
#define WINDOWSTATEDROPPABLECREATESELECT_H_

#include "WindowState.h"
#include "StateArgs.h"
#include "Button.h"

#define DROP_BUTTON_OFFSET 80
#define DROP_BUTTON_BASE_X 300
#define DROP_BUTTON_BASE_Y 150

#define SECOND_ROW_BASE_X 350

class WindowStateDroppableCreateSelect: public WindowState {
private:
	StateArgs argumentsToReturn;
	Button* laserDropButton;
	Button* missileDropButton;
	Button* spreadDropButton;
	Button* upgradeDropButton;
	Button* bombDropButton;
	Sprite* buttonContainer;
	Sprite* laserDropImage;
	Sprite* missileDropImage;
	Sprite* spreadDropImage;
	Sprite* bombDropImage;
	Sprite* upgradeDropImage;

public:
	WindowStateDroppableCreateSelect(StateArgs arguments);
	virtual ~WindowStateDroppableCreateSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEDROPPABLECREATESELECT_H_ */
