/*
 * BulletPattern.cpp
 *
 *  Created on: 27/04/2013
 *      Author: Vitor
 */

#include "BulletPattern.h"

BulletPattern::BulletPattern(Sprite* bulletSprite, bool circular) {
	this->bulletSprite = bulletSprite;
	this->circular = circular;
}

BulletPattern::~BulletPattern() {
	// TODO Auto-generated destructor stub
}

