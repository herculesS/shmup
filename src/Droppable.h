/*
 * Droppable.h
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#ifndef DROPPABLE_H_
#define DROPPABLE_H_

#include "GameObject.h"
#include "Vector2.h"
#include "Sprite.h"
#include "GameArea.h"
#include "Player.h"

#define MAX_FALL_SPEED 50.0
#define ACCELERATION 15.0

class Droppable: public GameObject {
protected:
	Vector2 velocity;
	Sprite* dropSprite;

	bool dead;

public:
	Droppable(Shape* shape, Sprite* dropSprite,
			Vector2 velocity = Vector2(0, 0));
	virtual ~Droppable();

	virtual int update(double dt);
	virtual void render(float cameraX = 0, float cameraY = 0);
	virtual void onCollisionWithPlayer(Player* player);

	bool isDead() const {
		return dead;
	}

	void setDead(bool dead) {
		this->dead = dead;
	}
};

#endif /* DROPPABLE_H_ */
