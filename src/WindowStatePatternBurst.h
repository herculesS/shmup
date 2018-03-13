/*
 * WindowStatePatternBurst.h
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEPATTERNBURST_H_
#define WINDOWSTATEPATTERNBURST_H_

#include "WindowState.h"
#include "StateArgs.h"
#include "LabeledTextField.h"
#include "LabeledCheckbox.h"
#include "Button.h"
#include "Sprite.h"
#include <string.h>
#include <string>

class WindowStatePatternBurst: public WindowState {
private:
	LabeledTextField* numShotsTextField;
	LabeledTextField* shotVelocityTextField;
	LabeledTextField* waitTimeTextField;
	LabeledTextField* numRepeatsTextField;
	LabeledTextField* bulletSpriteIndexTextField;
	LabeledCheckbox* circularBulletCheckbox;

public:
	WindowStatePatternBurst(StateArgs arguments);
	virtual ~WindowStatePatternBurst();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEPATTERNBURST_H_ */
