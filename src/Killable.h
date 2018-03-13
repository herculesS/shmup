/*
 * Killable.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Hercules
 */

#ifndef KILLABLE_H_
#define KILLABLE_H_
#include "GameObject.h"

class Killable: public GameObject {
protected:
	int life;
	bool dead;
	bool killed;
public:
	Killable(int life, Shape* shape);
	virtual void attemptToKill(int damage);
	virtual int update(double dt) = 0;
	virtual void render(float cameraX = 0, float cameraY = 0) = 0;
	bool isDead() const;
	bool wasKilled();
	virtual ~Killable();

	int getLife() const {
		return life;
	}

	void setLife(int life) {
		this->life = life;
	}
	void setDead(bool dead) {
		this->dead = dead;
	}
	void setKilled(bool killed) {
		this->killed = killed;
	}
};

#endif /* KILLABLE_H_ */
