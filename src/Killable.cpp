/*
 * Killable.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: Hercules
 */

#include "Killable.h"

Killable::Killable(int life, Shape* shape) :
		GameObject(shape) {
	this->life = life;
	this->dead = false;
	this->killed = false;
}
bool Killable::isDead() const {
	return dead;
}
void Killable::attemptToKill(int damage) {
	this->life = this->life - damage;
	if (this->life <= 0) {
		this->dead = true;
		this->killed = true;
	}
}
Killable::~Killable() {
	// TODO Auto-generated destructor stub
}
bool Killable::wasKilled() {
	return killed;
}

