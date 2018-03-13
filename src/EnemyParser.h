/*
 * EnemyParser.h
 *
 *  Created on: 26/06/2013
 *      Author: Vitor
 */

#ifndef ENEMYPARSER_H_
#define ENEMYPARSER_H_

#include "Enemy.h"
#include "OrbitingEnemy.h"
#include "BulletPatternFlower.h"
#include "BulletPatternBurst.h"
#include "BulletPatternSpread.h"
#include "DroppableWeapon.h"
#include "DroppableUpgrade.h"
#include "DroppableBomb.h"
#include "EnemyMoveAction.h"
#include "EnemyMoveStraightAction.h"
#include "EnemyShootAction.h"
#include "EnemyWaitAction.h"
#include "EnemyAddPatternAction.h"
#include "EnemyAddOrbitAction.h"
#include "EnemyStopShootingAction.h"
#include "EnemyDieAction.h"
#include "Sprite.h"
#include "Point.h"
#include "PlayerGunSpread.h"
#include "PlayerGunMissile.h"
#include "PlayerGunLaser.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <queue>
#include <deque>

#define UPGRADE_SPRITE_INDEX 0
#define SPREAD_SPRITE_INDEX 1
#define LASER_SPRITE_INDEX 2
#define MISSILE_SPRITE_INDEX 3
#define BOMB_SPRITE_INDEX 4

#define SPREAD_BULLET_INDEX 0
#define LASER_LEVEL1_SPRITE_INDEX 6
#define LASER_LEVEL2_SPRITE_INDEX 7
#define LASER_LEVEL3_SPRITE_INDEX 8
#define MISSILE_BULLET_INDEX 5

class EnemyParser {
private:
	static void parseActions(FILE* fp, Enemy* toParse,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target);
	static std::vector<BulletPattern*> parsePatterns(FILE* fp,
			std::vector<Sprite*> bulletSpriteVector);
	static BulletPattern* parsePattern(FILE* fp,
			std::vector<Sprite*> bulletSpriteVector);
	static std::vector<Enemy*> parseOrbits(FILE* fp,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target,
			Enemy* orbitCenter);
	static OrbitingEnemy* parseOrbit(FILE* fp,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target,
			Enemy* orbitCenter);
	static std::vector<Droppable*> parseDrops(FILE* fp,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Sprite*> bulletSpriteVector);

public:
	static Enemy* parseEnemy(std::string fileName,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target);
};

#endif /* ENEMYPARSER_H_ */
