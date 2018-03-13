/*
 * StateSplash.cpp
 *
 *  Created on: 07/06/2013
 *      Author: vitor
 */

#include "StateSplash.h"

StateSplash::StateSplash() {

}

StateSplash::~StateSplash() {
	unload();
}

void StateSplash::input() {
}

int StateSplash::update(double dt) {
	return nextState;
}

void StateSplash::render() {
}

void StateSplash::load(StateArgs arguments) {
	this->arguments = arguments;

	nextState = SDLBase::STATENOCHANGE;
}

StateArgs StateSplash::unload() {
	return StateArgs();
}
