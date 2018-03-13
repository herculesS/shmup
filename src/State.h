/*
 * State.h
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#ifndef STATE_H_
#define STATE_H_

#include "StateArgs.h"
#include "SDLBase.h"

class State {
protected:
	StateArgs arguments;
	int nextState;

public:
	State();
	virtual ~State();

	virtual void load(StateArgs arguments) = 0;
	virtual StateArgs unload() = 0;
	virtual void input() = 0;
	virtual int update(double dt) = 0;
	virtual void render() = 0;

	const StateArgs& getArguments() const {
		return arguments;
	}
};

#endif /* STATE_H_ */
