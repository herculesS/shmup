/*
 * DroppableWeapon.cpp
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#include "DroppableWeapon.h"

DroppableWeapon::DroppableWeapon(PlayerGun* weaponToDrop, Shape* shape,
		Sprite* dropSprite, Vector2 velocity) :
		Droppable(shape, dropSprite, velocity) {
	this->weaponToDrop = weaponToDrop;
}

DroppableWeapon::~DroppableWeapon() {
	// TODO Auto-generated destructor stub
}

void DroppableWeapon::onCollisionWithPlayer(Player* player) {
	Droppable::onCollisionWithPlayer(player);
	weaponToDrop->setGunLevel(player->getGun()->getGunLevel());
	player->setPlayerGun(weaponToDrop);
	weaponToDrop->setShooterPositionRef(player->getShape()->getCenterRef());
}
