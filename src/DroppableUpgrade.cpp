/*
 * DroppableUpgrade.cpp
 *
 *  Created on: 11/07/2013
 *      Author: vitor
 */

#include "DroppableUpgrade.h"

DroppableUpgrade::DroppableUpgrade(Shape* shape, Sprite* dropSprite,
		Vector2 velocity) :
		Droppable(shape, dropSprite, velocity) {
}

DroppableUpgrade::~DroppableUpgrade() {
	// TODO Auto-generated destructor stub
}

void DroppableUpgrade::onCollisionWithPlayer(Player* player) {
	Droppable::onCollisionWithPlayer(player);
	player->incrementPower();
}
