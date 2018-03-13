/*
 * BulletManager.h
 *
 *  Created on: 02/05/2013
 *      Author: Vitor
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include <vector>
#include "Bullet.h"
#include "CollisionManager.h"
#include "LaserBullet.h"
#include "Missile.h"
#include "Point.h"
#include "Vector2.h"
#include "GameObject.h"

class BulletManager {
private:
	static std::vector<Bullet*> enemyBulletList;
	static std::vector<Bullet*> playerBulletList;

	static bool valueInRange(float value, float min, float max);

public:
	static void instantiate(Point position, Vector2 velocity, bool enemyBullet,
			Sprite* bulletSprite, bool circular, int damage = 1);
	static void instantiateLaser(Point position, Vector2 velocity,
			bool enemyBullet, Sprite* bulletSprite, Point* shooterPositionRef,
			int damage = 1);
	static void instantiateMissile(Point position, Vector2 velocity,
			bool enemyBullet, Sprite* bulletSprite, Point* targetPositionRef,
			float rotateSpeed, int damage = 1);
	static Bullet* checkCollision(GameObject* target, bool targetIsEnemy);
	static std::vector<Bullet*> checkCollisions(GameObject* target,
			bool targetIsEnemy);
	static void cleanUp();
	static void update(double dt);
	static void render(float cameraX, float cameraY);
	static void removeOffScreenBullets(float areaWidth, float areaHeight);
	static void removeAllPlayerBullets();

};

#endif /* BULLETMANAGER_H_ */
