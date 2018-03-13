/*
 * WindowStateActionMoveStraight.h
 *
 *  Created on: 25/07/2013
 *      Author: vitor
 */

#ifndef WINDOWStateACTIONMOVESTRAIGHT_H_
#define WINDOWStateACTIONMOVESTRAIGHT_H_

#include "WindowState.h"
#include "LabeledTextField.h"

class WindowStateActionMoveStraight: public WindowState {
private:
	LabeledTextField* heightTextField;
	LabeledTextField* speedTextField;

public:
	WindowStateActionMoveStraight(StateArgs arguments);
	virtual ~WindowStateActionMoveStraight();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWStateACTIONMOVESTRAIGHT_H_ */
