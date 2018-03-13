/*
 * WindowStatePatternFlower.h
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEPATTERNFLOWER_H_
#define WINDOWSTATEPATTERNFLOWER_H_

#include "WindowState.h"
#include "LabeledTextField.h"
#include "LabeledCheckbox.h"

class WindowStatePatternFlower: public WindowState {
private:
	LabeledTextField* numShotsTextField;
	LabeledTextField* shotVelocityTextField;
	LabeledTextField* waitTimeTextField;
	LabeledTextField* angleTextField;
	LabeledTextField* numRepeatsTextField;
	LabeledTextField* bulletSpriteIndexTextField;
	LabeledCheckbox* circularBulletCheckbox;
	LabeledCheckbox* clockwiseCheckbox;

public:
	WindowStatePatternFlower(StateArgs arguments);
	virtual ~WindowStatePatternFlower();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();

};

#endif /* WINDOWSTATEPATTERNFLOWER_H_ */
