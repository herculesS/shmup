/*
 * WindowStateActionSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEACTIONSELECT_H_
#define WINDOWSTATEACTIONSELECT_H_

#include "WindowState.h"
#include "Sprite.h"
#include "Button.h"
#include <algorithm>

#define ACTION_BUTTONS_X 250
#define NUM_ACTIONS_LINE 5
#define ACTION_BUTTONS_Y 150
#define ACTION_BUTTONS_OFFSET 80

#define SWAP_BUTTON_X 770
#define SWAP_BUTTON_Y 345

#define NEW_ACTION_X 770
#define NEW_ACTION_Y 300

#define DELETE_ACTION_BUTTON_X 770
#define DELETE_ACTION_BUTTON_Y 265

class WindowStateActionSelect: public WindowState {
private:
	StateArgs arguments;
	std::vector<Button*> actionButtonVector;
	int nextStateVector[50];
	int clickedButtonIndex;

	int actionIndexes[2];
	int swapCounter;
	bool swapping;

	bool creatingNewAction;
	bool deletingAction;

	Button* newActionButton;
	Button* swapButton;
	Button* deleteActionButton;
	Sprite* deleteActionImage;
	Sprite* dieActionImage;
	Sprite* moveActionImage;
	Sprite* moveStraightActionImage;
	Sprite* addPatternActionImage;
	Sprite* shootImage;
	Sprite* stopShootingImage;
	Sprite* waitActionImage;
	Sprite* addOrbitActionImage;
	Sprite* swapButtonImage;
	Sprite* swapButtonContainer;
	Sprite* buttonContainerImage;
	Sprite* newActionImage;

	void createNewButton(std::string actionName);
	Sprite* selectActionImage(std::string actionName);
	int selectButtonState(std::string actionName);

	void deleteAction(int index);
	void resetButtonsPosition();

	void swapActions(int firstIndex, int secondIndex);

public:
	WindowStateActionSelect(StateArgs arguments);
	virtual ~WindowStateActionSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEACTIONSELECT_H_ */
