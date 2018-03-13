/*
 * WindowStateActionCreateSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEACTIONCREATESELECT_H_
#define WINDOWSTATEACTIONCREATESELECT_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"

#define ACTION_BUTTON_BASE_X 400
#define ACTION_BUTTON_BASE_Y 300
#define ACTION_BUTTON_OFFSET 80

class WindowStateActionCreateSelect: public WindowState {
private:
	StateArgs argumentsToReturn;
	Button* moveButton;
	Button* moveStraightButton;
	Button* dieButton;
	Button* addPatternButton;
	Button* shootButton;
	Button* stopShootingButton;
	Button* waitActionButton;
	Sprite* dieActionImage;
	Sprite* moveActionImage;
	Sprite* moveStraightActionImage;
	Sprite* addPatternActionImage;
	Sprite* shootImage;
	Sprite* stopShootingImage;
	Sprite* waitActionImage;
	Sprite* buttonContainerImage;

	bool creatingNewAddActionPattern;

public:
	WindowStateActionCreateSelect(StateArgs arguments);
	virtual ~WindowStateActionCreateSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEACTIONCREATESELECT_H_ */
