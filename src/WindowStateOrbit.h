/*
 * WindowStateOrbit.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEORBIT_H_
#define WINDOWSTATEORBIT_H_

#include "WindowState.h"
#include "LabeledTextField.h"
#include "LabeledCheckbox.h"
#include "StateArgs.h"
#include "Button.h"
#include "Sprite.h"

#define ORBIT_BUTTON_X 400
#define ORBIT_BUTTON_Y 450

class WindowStateOrbit: public WindowState {
private:
	LabeledTextField* initialAngleTextField;
	LabeledTextField* speedTextField;
	LabeledTextField* radiusTextField;
	LabeledCheckbox* clockwiseCheckbox;
	LabeledTextField* enemyFileNameTextField;

	Button* orbitButton;
	Sprite* orbitButtonImage;
	Sprite* buttonContainer;

public:
	WindowStateOrbit(StateArgs arguments);
	virtual ~WindowStateOrbit();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEORBIT_H_ */
