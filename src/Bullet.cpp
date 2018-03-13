/*
 * Bullet.cpp
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#include "Bullet.h"

Bullet::Bullet(Vector2 velocity, bool isEnemy, Sprite* bulletSprite,
		Shape* shape, int damage) :
		GameObject(shape) {
	this->bulletSprite = bulletSprite;
	this->velocity = velocity;
	this->enemy = isEnemy;
	this->speed = velocity.length();
	this->dead = false;
	this->damage = damage;

}

Bullet::~Bullet() {
}

int Bullet::update(double dt) {
	// Equivalente a posicao += velocidade
	this->shape->setCenter(
			this->shape->getCenterRef()->addVector(
					this->velocity.constantProduct(dt)));
	return 0;
}

void Bullet::render(float cameraX, float cameraY) {

	this->bulletSprite->rotoZoom(
			atan2(-velocity.getY(), velocity.getX()) * 180 / M_PI, 1, 1, false);
	bulletSprite->render(shape->getCenterRef()->getX() - cameraX,
			shape->getCenterRef()->getY() - cameraY, true,
			GameArea::getSurface());
}
void Bullet::explode() {
	int numOfSprites[1] = { 7 };
	AnimationManager::instantiate(*shape->getCenterRef(),
			new Animation("../gfx/BulletExplosion.png", 50, 1, numOfSprites, 31,
					false));
	onHitSound = new Sound("../sfx/Projectile.wav");
	onHitSound->play(1);
	onHitSound->setVolume(10);
}
void Bullet::onCollisionWith(Killable* toKill) {
	setDead(true);
	explode();
	SoundEraser::EraseSound(onHitSound);
	toKill->attemptToKill(this->damage);
}
