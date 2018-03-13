/*
 * Player.h
 *
 *  Created on: Jun 18, 2013
 *      Author: AT WORK
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Killable.h"
#include "PlayerGunSpread.h"
#include "PlayerGunLaser.h"
#include "Timer.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "BombManager.h"
#include "Animation.h"
#include "InputManager.h"
#include "Vector2.h"
#include "GameArea.h"

#define N_UPGRADES_NEXT_LEVEL 5
#define INVINCIBILITY_TIME 2500
#define REVIVAL_TIME 2000
#define INVINCIBILITY_BLINK_TIME 20

class Player: public Killable {
private:
	int gunPower;
	Animation* animation;
	Animation* deathAnimation;
	Sprite* focusSprite;
	PlayerGun* gun;
	float speed;
	float focusSpeedReduction;
	Vector2 vecSpeed;
	Point target;

	bool bombing;
	int numBombs;

	bool reviving;
	bool invincible;
	bool indestructible;
	bool showBlank;
	Timer invincibilityTimer;
	Timer revivalTimer;
	Timer invincibilityBlinkTimer;

	Vector2 directionVector;

	void setInvincibility();

public:
	Player(Animation* animation, Sprite* focusSprite, PlayerGun* gun,
			Shape* shape, Animation* deathAnimation);
	void setTarget(Point target);
	int update(double dt);
	void render(float cameraX, float cameraY);
	void attemptToKill(int damage);
	bool isInvincible();

	void incrementPower() {
		this->gunPower++;
	}

	void incrementBombs() {
		this->numBombs++;
	}

	void setPlayerGun(PlayerGun* gun) {
		this->gun = gun;
	}

	virtual ~Player();

	PlayerGun* getGun() {
		return gun;
	}

	int getNumBombs() {
		return numBombs;
	}
	void setIndestructible(bool toSet) {
		indestructible = toSet;
	}
};

#endif /* PLAYER_H_ */
