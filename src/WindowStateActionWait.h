/*
 * WindowStateActionWait.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEACTIONWAIT_H_
#define WINDOWSTATEACTIONWAIT_H_

#include "WindowState.h"
#include "LabeledTextField.h"
#include "StateArgs.h"

class WindowStateActionWait: public WindowState {
private:
	LabeledTextField* timeTextField;

public:
	WindowStateActionWait(StateArgs arguments);
	virtual ~WindowStateActionWait();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEACTIONWAIT_H_ */
