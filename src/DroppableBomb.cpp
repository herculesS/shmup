/*
 * DroppableBomb.cpp
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#include "DroppableBomb.h"

DroppableBomb::DroppableBomb(Shape* shape, Sprite* dropSprite, Vector2 velocity) :
		Droppable(shape, dropSprite, velocity) {
}

DroppableBomb::~DroppableBomb() {
	// TODO Auto-generated destructor stub
}

void DroppableBomb::onCollisionWithPlayer(Player* player) {
	Droppable::onCollisionWithPlayer(player);
	player->incrementBombs();
}
