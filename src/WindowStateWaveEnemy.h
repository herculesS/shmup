/*
 * WindowStateWaveEnemy.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEWAVEENEMY_H_
#define WINDOWSTATEWAVEENEMY_H_

#include "WindowState.h"
#include "StateArgs.h"
#include "Button.h"
#include "LabeledTextField.h"

#define ENEMY_BUTTON_X 400
#define ENEMY_BUTTON_Y 400

class WindowStateWaveEnemy: public WindowState {
private:
	LabeledTextField* xPositionTextField;
	LabeledTextField* yPositionTextField;
	LabeledTextField* timeTextField;
	LabeledTextField* enemyFileTextField;
	Button* enemyButton;
	Sprite* enemyButtonImage;
	Sprite* enemyButtonContainer;

public:
	WindowStateWaveEnemy(StateArgs arguments);
	virtual ~WindowStateWaveEnemy();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEWAVEENEMY_H_ */
