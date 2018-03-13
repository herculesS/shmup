/*
 * Bullet.h
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Animation.h"
#include "AnimationManager.h"
#include "GameArea.h"
#include "Point.h"
#include "Vector2.h"
#include "GameObject.h"
#include "Shape.h"
#include "Killable.h"
#include "Sound.h"
#include "SoundEraser.h"
#include <math.h>

class Bullet: public GameObject {
protected:
	Sprite* bulletSprite;
	Vector2 velocity;
	float speed;
	bool enemy;
	bool dead;
	int damage;
	Sound* onHitSound;

public:
	Bullet(Vector2 velocity, bool isEnemy, Sprite* bulletSprite, Shape* shape,
			int damage = 1);
	virtual ~Bullet();
	virtual int update(double dt);
	virtual void render(float cameraX, float cameraY);
	void onCollisionWith(Killable* toKill);
	virtual void explode();

	const Vector2& getVelocity() const {
		return velocity;
	}

	void setVelocity(const Vector2& velocity) {
		this->velocity = velocity;
	}
	void setdamage(int damage) {
		this->damage = damage;
	}
	bool isDead() const {
		return dead;
	}

	void setDead(bool dead) {
		this->dead = dead;
	}
};

#endif /* BULLET_H_ */
