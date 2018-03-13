/*
 * BombManager.h
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#ifndef BOMBMANAGER_H_
#define BOMBMANAGER_H_

#include "Bomb.h"
#include "GameObject.h"

class BombManager {
private:
	static Bomb* bomb;

public:
	static void instantiateBomb(Point position);
	static void update(double dt);
	static bool checkCollision(GameObject* toCheck);

	static Bomb* getBomb();
};

#endif /* BOMBMANAGER_H_ */
