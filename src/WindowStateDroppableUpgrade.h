/*
 * WindowStateDroppableUpgrade.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEDROPPABLEUPGRADE_H_
#define WINDOWSTATEDROPPABLEUPGRADE_H_

#include "WindowState.h"
#include "LabeledTextField.h"

class WindowStateDroppableUpgrade: public WindowState {
private:
	LabeledTextField* dropNumberTextField;

public:
	WindowStateDroppableUpgrade(StateArgs arguments);
	virtual ~WindowStateDroppableUpgrade();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEDROPPABLEUPGRADE_H_ */
