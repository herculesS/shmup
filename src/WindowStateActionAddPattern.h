/*
 * WindowStateActionAddPattern.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEACTIONADDPATTERN_H_
#define WINDOWSTATEACTIONADDPATTERN_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"
#include "StateArgs.h"
#include <string.h>

#define PATTERN_BUTTON_X 400
#define PATTERN_BUTTON_Y 150

class WindowStateActionAddPattern: public WindowState {
private:
	StateArgs arguments;
	Button* patternButton;
	Sprite* buttonContainerImage;
	Sprite* flowerPatternImage;
	Sprite* spreadPatternImage;
	Sprite* burstPatternImage;

	int nextPatternState;

public:
	WindowStateActionAddPattern(StateArgs arguments);
	virtual ~WindowStateActionAddPattern();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEACTIONADDPATTERN_H_ */
