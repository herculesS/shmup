/*
 * WindowStateActionMove.h
 *
 *  Created on: 25/07/2013
 *      Author: Vitor
 */

#ifndef WINDOWSTATEACTIONMOVE_H_
#define WINDOWSTATEACTIONMOVE_H_

#include "WindowState.h"
#include "LabeledTextField.h"
#include "StateArgs.h"

class WindowStateActionMove: public WindowState {
private:
	LabeledTextField* xPositionTextField;
	LabeledTextField* yPositionTextField;
	LabeledTextField* speedTextField;

public:
	WindowStateActionMove(StateArgs arguments);
	virtual ~WindowStateActionMove();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEACTIONMOVE_H_ */
