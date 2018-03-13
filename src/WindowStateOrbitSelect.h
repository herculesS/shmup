/*
 * WindowStateOrbitSelect.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEORBITSELECT_H_
#define WINDOWSTATEORBITSELECT_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"

#define ORBIT_BUTTONS_X 250
#define NUM_ORBITS_LINE 5
#define ORBIT_BUTTONS_Y 150
#define ORBIT_BUTTONS_OFFSET 80

#define DELETE_ORBIT_BUTTON_X 760
#define DELETE_ORBIT_BUTTON_Y 265

class WindowStateOrbitSelect: public WindowState {
private:
	StateArgs arguments;
	std::vector<Button*> orbitButtonVector;
	int clickedButtonIndex;

	Button* deleteOrbitButton;
	Sprite* deleteOrbitImage;
	Sprite* deleteOrbitContainer;

	bool deletingOrbit;

	Sprite* orbitButtonImage;
	Sprite* buttonContainer;

	void createNewButton();
	void deleteOrbit(int index);
	void resetButtonsPosition();

public:
	WindowStateOrbitSelect(StateArgs arguments);
	virtual ~WindowStateOrbitSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEORBITSELECT_H_ */
