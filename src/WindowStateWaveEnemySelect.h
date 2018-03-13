/*
 * WindowStateWaveEnemySelect.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEWAVEENEMYSELECT_H_
#define WINDOWSTATEWAVEENEMYSELECT_H_

#include "WindowState.h"
#include "Button.h"
#include "Sprite.h"
#include "StateArgs.h"
#include "Text.h"

#define ENEMY_BUTTONS_X 250
#define NUM_ENEMIES_LINE 5
#define ENEMY_BUTTONS_Y 150
#define ENEMY_BUTTONS_OFFSET 80

#define SUBTITLE_POS_X 400
#define SUBTITLE_POS_Y 50

class WindowStateWaveEnemySelect: public WindowState {
private:
	Text* subTitle;
	std::string waveFileName;
	std::vector<std::vector<std::string> > waveEnemyVector;
	std::vector<Button*> waveEnemyButtonVector;
	int clickedButtonIndex;

	Sprite* waveEnemyImage;
	Sprite* waveEnemyContainer;

	void initVector(const char* waveFileName);

public:
	WindowStateWaveEnemySelect(StateArgs arguments);
	virtual ~WindowStateWaveEnemySelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEWAVEENEMYSELECT_H_ */
