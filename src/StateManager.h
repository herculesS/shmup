/*
 * StateManager.h
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#define FPS 60.0

#include "SDLBase.h"
#include "State.h"
#include "StateArgs.h"
#include "StateSplash.h"
#include "StateGame.h"
#include "StateMenu.h"
#include "StateEditor.h"
#include "StateWin.h"
#include <stack>

class StateManager {
private:
	std::stack<State*> stateStack;
	bool quit;
	StateArgs args;

public:
	StateManager();
	virtual ~StateManager();

	void run();
};

#endif /* STATEMANAGER_H_ */
