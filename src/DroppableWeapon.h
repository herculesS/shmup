/*
 * DroppableWeapon.h
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#ifndef DROPPABLEWEAPON_H_
#define DROPPABLEWEAPON_H_

#include "Droppable.h"
#include "PlayerGun.h"
#include "Sprite.h"

class DroppableWeapon: public Droppable {
private:
	PlayerGun* weaponToDrop;

public:
	DroppableWeapon(PlayerGun* weaponToDrop, Shape* shape, Sprite* dropSprite,
			Vector2 velocity = Vector2(0, 0));
	virtual ~DroppableWeapon();

	void onCollisionWithPlayer(Player* player);

};

#endif /* DROPPABLEWEAPON_H_ */
