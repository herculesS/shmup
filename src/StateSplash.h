/*
 * StateSplash.h
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#ifndef STATESPLASH_H_
#define STATESPLASH_H_

#include "State.h"
#include "Text.h"
#include "Music.h"
#include "Sprite.h"
#include "StateArgs.h"
#include "InputManager.h"

class StateSplash: public State {
public:
	StateSplash();
	virtual ~StateSplash();
	void load(StateArgs arguments);
	StateArgs unload();
	void input();
	int update(double dt);
	void render();

};

#endif /* STATESPLASH_H_ */
