/*
 * PlayerGun.cpp
 *
 *  Created on: 22/06/2013
 *      Author: Vitor
 */

#include "PlayerGun.h"

PlayerGun::PlayerGun(int gunLevel, Sprite* bulletSprite,
		Point* shooterPositionRef) {
	this->gunLevel = gunLevel;
	this->bulletSprite = bulletSprite;
	this->shooterPositionRef = shooterPositionRef;
}

PlayerGun::~PlayerGun() {
	// TODO Auto-generated destructor stub
}

