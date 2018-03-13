/*
 * StateManager.cpp
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#include "StateManager.h"

StateManager::StateManager() {
	SDLBase::inicializaSDL();
	stateStack.push(new StateMenu());
	stateStack.top()->load(StateArgs());
	quit = false;
}

StateManager::~StateManager() {
	while (!stateStack.empty()) {
		stateStack.pop();
	}
	SDLBase::finalizaSDL();
}

void StateManager::run() {
	int timeInMs, lastTimeInMs;
	double timeSpentOnFrame;
	double dt;

	dt = 0.0;
	timeInMs = 0;
	lastTimeInMs = 0;

	while (!quit) {
		timeInMs = SDL_GetTicks();
		dt = (timeInMs - lastTimeInMs) * 0.001;
		lastTimeInMs = timeInMs;

		InputManager::getInstance()->update();

		stateStack.top()->input();

		switch (stateStack.top()->update(dt)) {
		case SDLBase::STATENOCHANGE:
			break;
		case SDLBase::STATEQUIT:
			quit = true;
			break;
		case SDLBase::STATEDESTROY:
			args = stateStack.top()->unload();
			stateStack.pop();
			break;
		case SDLBase::STATEGAME:
			stateStack.push(new StateGame());
			stateStack.top()->load(StateArgs());
			break;
		case SDLBase::STATEEDITOR:
			stateStack.push(new StateEditor());
			stateStack.top()->load(StateArgs());
			break;
		case SDLBase::STATELOSE:
			args = stateStack.top()->unload();
			stateStack.pop();
			break;
		case SDLBase::STATEWIN:
			args = stateStack.top()->unload();
			stateStack.pop();
			stateStack.push(new StateWin());
			stateStack.top()->load(args);
			break;
		case SDLBase::STATEMENU:
			args = stateStack.top()->unload();
			stateStack.pop();
			stateStack.push(new StateMenu());
			stateStack.top()->load(args);
			break;

		default:
			fprintf(stderr, "ERRO! Tentando mudar para estado inexistente\n");
			exit(1);
		}

		stateStack.top()->render();
		SDLBase::atualizarTela();

		timeSpentOnFrame = (SDL_GetTicks() - timeInMs) * 0.001;
		if (timeSpentOnFrame < 1 / FPS)
			SDL_Delay((1 / FPS - timeSpentOnFrame) * 1000);
	}

}
