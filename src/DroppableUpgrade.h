/*
 * DroppableUpgrade.h
 *
 *  Created on: 11/07/2013
 *      Author: vitor
 */

#ifndef DROPPABLEUPGRADE_H_
#define DROPPABLEUPGRADE_H_

#include "Droppable.h"
#include "Player.h"

class DroppableUpgrade: public Droppable {
public:
	DroppableUpgrade(Shape* shape, Sprite* dropSprite, Vector2 velocity =
			Vector2(0, 0));
	virtual ~DroppableUpgrade();

	void onCollisionWithPlayer(Player* player);
};

#endif /* DROPPABLEUPGRADE_H_ */
