/*
 * WindowStatePatternSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEPATTERNSELECT_H_
#define WINDOWSTATEPATTERNSELECT_H_

#include "WindowState.h"
#include "Sprite.h"
#include "Button.h"

#define PATTERN_BUTTONS_X 250
#define NUM_BUTTONS_LINE 5
#define PATTERN_BUTTONS_Y 150
#define PATTERN_BUTTONS_OFFSET 80

#define NEW_PATTERN_BUTTON_X 760
#define NEW_PATTERN_BUTTON_Y 300

#define DELETE_PATTERN_BUTTON_X 760
#define DELETE_PATTERN_BUTTON_Y 265

class WindowStatePatternSelect: public WindowState {
private:
	bool creatingNewPattern;
	bool deletingPattern;
	StateArgs arguments;
	std::vector<Button*> patternButtonVector;
	int nextStateVector[50];
	int clickedButtonIndex;
	Sprite* buttonContainerImage;
	Sprite* spreadPatternImage;
	Sprite* burstPatternImage;
	Sprite* flowerPatternImage;
	Button* newPatternButton;
	Sprite* newPatternContainerImage;
	Sprite* newPatternImage;
	Button* deletePatternButton;
	Sprite* deletePatternImage;

	Sprite* selectPatternImage(std::string patternName);
	int selectButtonState(std::string patternName);
	void createNewButton(std::string patternName);
	void deletePattern(int index);
	void resetButtonsPosition();

public:
	WindowStatePatternSelect(StateArgs arguments);
	virtual ~WindowStatePatternSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEPATTERNSELECT_H_ */
