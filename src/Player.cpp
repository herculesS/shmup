/*
 * Player.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: AT WORK
 */

#include "Player.h"
#define PLAYER_NUMBER_OF_LIVES 4

Player::Player(Animation* animation, Sprite* focusSprite, PlayerGun* gun,
		Shape* shape, Animation* deathAnimation) :
		Killable(PLAYER_NUMBER_OF_LIVES, shape) {
	this->animation = animation;
	this->focusSprite = focusSprite;
	this->focusSprite->setHidden(true);
	this->deathAnimation = deathAnimation;
	this->gunPower = 0;
	speed = 200.0;
	focusSpeedReduction = 0.3;
	vecSpeed.setX(0);
	vecSpeed.setY(0);
	invincible = false;
	reviving = false;
	showBlank = false;
	indestructible = false;

	bombing = false;
	numBombs = 4;

	this->gun = gun;

	directionVector.setX(0);
	directionVector.setY(-1);
	invincibilityTimer.start(0);
	this->deathAnimation->setHidden(true);
}

void Player::setInvincibility() {
	this->invincibilityTimer.start(INVINCIBILITY_TIME);
	invincibilityBlinkTimer.start(INVINCIBILITY_BLINK_TIME);
	invincible = true;
}

int Player::update(double dt) {
	vecSpeed.setX(0);
	vecSpeed.setY(0);
	focusSprite->setHidden(true);

	invincibilityTimer.update();
	invincibilityBlinkTimer.update();
	if (invincibilityTimer.isDone()) {
		invincible = false;
		animation->setHidden(false);
	}
	if (invincible) {
		if (invincibilityBlinkTimer.isDone()) {
			if (showBlank) {
				this->animation->setHidden(true);
				showBlank = false;
			} else {
				this->animation->setHidden(false);
				showBlank = true;
			}
			invincibilityBlinkTimer.start(INVINCIBILITY_BLINK_TIME);
		}
	}

	// Se não há bombas sendo explodidas, então o player não está bombing
	if (!BombManager::getBomb()) {
		bombing = false;
	}

	// Checa se o player não está morto, habilitando seus movimentos
	if (!dead) {
		animation->setCurrentRow(0);
		if (InputManager::getInstance()->isKeyPressed(SDLK_UP)) {
			vecSpeed.setY(-speed);
			animation->setCurrentRow(1);
		}
		if (InputManager::getInstance()->isKeyPressed(SDLK_DOWN)) {
			vecSpeed.setY(speed);
			animation->setCurrentRow(4);
		}
		if (InputManager::getInstance()->isKeyPressed(SDLK_LEFT)) {
			vecSpeed.setX(-speed);
			animation->setCurrentRow(2);
		}
		if (InputManager::getInstance()->isKeyPressed(SDLK_RIGHT)) {
			vecSpeed.setX(speed);
			animation->setCurrentRow(3);
		}

		// Tiro
		if (InputManager::getInstance()->isKeyPressed(SDLK_z)) {
			// A arma s� precisa da informa��o de onde o jogador est� apontando
			// em termos de velocidade de tiro e ela cuida do resto
			gun->shoot(*(getShape()->getCenterRef()), directionVector, &target);
		}

		if (InputManager::getInstance()->isKeyUp(SDLK_z)) {
			gun->stopShooting();
		}

		// Bomba
		if (InputManager::getInstance()->isKeyDown(SDLK_x) && !bombing
				&& numBombs > 0) {
			bombing = true;
			numBombs--;
			setInvincibility();
			animation->setHidden(true);
			BombManager::instantiateBomb(*shape->getCenterRef());
		}

		// Se o SHIFT esquerdo estiver apertando, o player tem sua velocidade reduzida
		if (InputManager::getInstance()->isKeyPressed(SDLK_LSHIFT)) {
			vecSpeed = vecSpeed.constantProduct(focusSpeedReduction);
			focusSprite->setHidden(false);
		}
	} else {	// Caso contrário, devemos tratar a morte
		animation->setHidden(true);
		if (!reviving) {
			reviving = true;
			revivalTimer.start(REVIVAL_TIME);
		}

		this->deathAnimation->update(dt);
		if (deathAnimation->isEnded()) {
			deathAnimation->setHidden(true);
		}

		revivalTimer.update();
		if (revivalTimer.isDone()) {
			reviving = false;
			dead = false;
			deathAnimation->reset();
			shape->setCenter(Point(300, 500));
			setInvincibility();
		}
	}

	if (gunPower > N_UPGRADES_NEXT_LEVEL) {
		gun->setGunLevel(gun->getGunLevel() + 1);
		gunPower -= N_UPGRADES_NEXT_LEVEL;
	}

	this->shape->setX(shape->getX() + vecSpeed.getX() * dt);
	this->shape->setY(shape->getY() + vecSpeed.getY() * dt);
	this->animation->update(dt);

	return 0;
}

void Player::setTarget(Point target) {
	this->target = target;
}

void Player::render(float cameraX, float cameraY) {
	this->animation->render(this->shape->getX() - cameraX,
			this->shape->getY() - cameraY, true, GameArea::getSurface());
	this->focusSprite->render(this->shape->getX() - cameraX,
			this->shape->getY() - cameraY, true, GameArea::getSurface());
	this->deathAnimation->render(this->shape->getX() - cameraX,
			this->shape->getY() - cameraY, true, GameArea::getSurface());
}

void Player::attemptToKill(int damage) {
	if (!invincible && !indestructible) {
		this->setLife(this->getLife() - 1);
		this->setDead(true);
		this->animation->setHidden(true);
		this->deathAnimation->setHidden(false);
	}
}

bool Player::isInvincible() {
	return invincible;
}

Player::~Player() {
}

