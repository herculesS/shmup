/*
 * WindowStatePatternSpread.h
 *
 *  Created on: 25/07/2013
 *      Author: Vitor
 */

#ifndef WINDOWSTATEPATTERNSPREAD_H_
#define WINDOWSTATEPATTERNSPREAD_H_

#include "WindowState.h"
#include "LabeledTextField.h"
#include "LabeledCheckbox.h"
#include "StateArgs.h"

class WindowStatePatternSpread: public WindowState {
private:
	LabeledTextField* numShotsTextField;
	LabeledTextField* shotVelocityTextField;
	LabeledTextField* waitTimeTextField;
	LabeledTextField* arcTextField;
	LabeledTextField* numRepeatsTextField;
	LabeledTextField* bulletSpriteIndexTextField;
	LabeledCheckbox* circularBulletCheckbox;

public:
	WindowStatePatternSpread(StateArgs arguments);
	virtual ~WindowStatePatternSpread();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEPATTERNSPREAD_H_ */
