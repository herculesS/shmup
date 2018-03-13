/*
 * StateEditor.h
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#ifndef STATEEDITOR_H_
#define STATEEDITOR_H_

#include "State.h"
#include "StateArgs.h"
#include "Sprite.h"
#include "InputManager.h"
#include "LabeledTextField.h"
#include "Music.h"
#include "WindowState.h"
#include "WindowStatePatternBurst.h"
#include "WindowStatePatternFlower.h"
#include "WindowStatePatternSpread.h"
#include "WindowStateActionMove.h"
#include "WindowStateActionMoveStraight.h"
#include "WindowStateActionWait.h"
#include "WindowStateActionAddPattern.h"
#include "WindowStatePatternSelect.h"
#include "WindowStatePatternCreateSelect.h"
#include "WindowStateActionSelect.h"
#include "WindowStateActionCreateSelect.h"
#include "WindowStateDroppableUpgrade.h"
#include "WindowStateDroppableSelect.h"
#include "WindowStateDroppableCreateSelect.h"
#include "WindowStateEnemyAttributeSelect.h"
#include "WindowStateOrbit.h"
#include "WindowStateOrbitSelect.h"
#include "WindowStateWaveEnemy.h"
#include "WindowStateWaveEnemySelect.h"
#include <stack>

#define EXIT_EDITOR_BUTTON_X 770
#define EXIT_EDITOR_BUTTON_Y 30
#define GO_BACK_BUTTON_X 30
#define GO_BACK_BUTTON_Y 30
#define CONFIRM_BUTTON_X 90
#define CONFIRM_BUTTON_Y 30

class StateEditor: public State {
private:
	bool quitGame;
	bool quitEditor;
	bool goBack;
	bool confirmChanges;
	Sprite* background;
	Button* exitEditorButton;
	Button* goBackButton;
	Button* confirmButton;
	Sprite* goBackButtonSprite;
	Sprite* confirmButtonSprite;
	Sprite* exitEditorSprite;
	Sprite* exitEditorSpriteContainer;

	Music* backgroundMusic;

	std::stack<WindowState*> windowStateStack;

	void killTopState();

public:
	StateEditor();
	virtual ~StateEditor();

	void load(StateArgs arguments);
	StateArgs unload();
	void input();
	int update(double dt);
	void render();
};

#endif /* STATEEDITOR_H_ */
