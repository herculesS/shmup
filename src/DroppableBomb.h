/*
 * DroppableBomb.h
 *
 *  Created on: 19/07/2013
 *      Author: vitor
 */

#ifndef DROPPABLEBOMB_H_
#define DROPPABLEBOMB_H_

#include "Droppable.h"

class DroppableBomb: public Droppable {
public:
	DroppableBomb(Shape* shape, Sprite* dropSprite,
			Vector2 velocity = Vector2(0, 0));
	virtual ~DroppableBomb();

	void onCollisionWithPlayer(Player* player);
};

#endif /* DROPPABLEBOMB_H_ */
