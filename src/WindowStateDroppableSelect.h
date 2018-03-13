/*
 * WindowStateDroppableSelect.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEDROPPABLESELECT_H_
#define WINDOWSTATEDROPPABLESELECT_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"

#define DROPS_BASE_X 250
#define DROPS_BASE_Y 150
#define NUM_DROPS_LINE 5
#define DROPS_OFFSET 80

#define NEW_DROP_X 770
#define NEW_DROP_Y 300

#define DELETE_DROP_BUTTON_X 770
#define DELETE_DROP_BUTTON_Y 265

class WindowStateDroppableSelect: public WindowState {
private:
	StateArgs arguments;
	std::vector<Button*> dropButtonVector;
	int nextStateVector[50];
	int clickedButtonIndex;

	bool creatingNewDrop;
	bool deletingDrop;

	Button* newDropButton;
	Button* deleteDropButton;
	Sprite* laserDropImage;
	Sprite* missileDropImage;
	Sprite* spreadDropImage;
	Sprite* bombDropImage;
	Sprite* upgradeDropImage;
	Sprite* buttonContainer;
	Sprite* newDropContainer;
	Sprite* newDropImage;
	Sprite* deleteDropImage;

	void createNewButton(std::string dropName);
	void resetButtonsPosition();
	void deleteDrop(int index);
	Sprite* selectDropImage(std::string dropName);
	int selectButtonState(std::string dropName);

public:
	WindowStateDroppableSelect(StateArgs arguments);
	virtual ~WindowStateDroppableSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEDROPPABLESELECT_H_ */
