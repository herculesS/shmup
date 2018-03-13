/*
 * WindowStatePatternCreateSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEPATTERNCREATESELECT_H_
#define WINDOWSTATEPATTERNCREATESELECT_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"

#define BUTTONS_BASE_X 400
#define BUTTONS_BASE_Y 150

#define BUTTON_OFFSET 80

class WindowStatePatternCreateSelect: public WindowState {
private:
	StateArgs returnArguments;
	Button* newBurstButton;
	Button* newFlowerButton;
	Button* newSpreadButton;
	Sprite* spreadButtonImage;
	Sprite* burstButtonImage;
	Sprite* flowerButtonImage;
	Sprite* buttonContainerImage;

public:
	WindowStatePatternCreateSelect(StateArgs arguments);
	virtual ~WindowStatePatternCreateSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEPATTERNCREATESELECT_H_ */
