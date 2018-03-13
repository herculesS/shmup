/*
 * EnemyParser.cpp
 *
 *  Created on: 26/06/2013
 *      Author: Vitor
 */

#include "EnemyParser.h"

Enemy* EnemyParser::parseEnemy(std::string fileName,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target) {

	FILE* enemyFile = fopen(fileName.c_str(), "r");
	char stringRead[50];
	int life;
	int spriteIndex;
	int points;
	Point initialPosition(0, -300);
	std::vector<BulletPattern*> parsedBulletPatterns;
	std::vector<Enemy*> parsedOrbits;
	std::vector<Droppable*> parsedDrops;

	Enemy* toParse = NULL;

	if (enemyFile == NULL) {
		fprintf(stderr, "EnemyParser: Nao conseguiu abrir o arquivo %s.\n",
				fileName.c_str());
		exit(1);
	}

	// Loop que varre o arquivo todo procurando as palavras chaves
	// e construindo o que deve baseado nelas
	//
	// OBS: O inimigo deve ter a vida, a posicao inicial e seu sprite definidos j�
	// antes de ler seus actions!! A defini��o das �rbitas deve, tamb�m, vir depois
	// da defini��o das actions!!
	while (!feof(enemyFile)) {
		fscanf(enemyFile, "%s", stringRead);

		if (strcasecmp(stringRead, "patterns") == 0) {
			parsedBulletPatterns = parsePatterns(enemyFile, bulletSpriteVector);
		} else if (strcasecmp(stringRead, "actions") == 0) {
			toParse = new Enemy(enemySpriteVector.at(spriteIndex), target,
					new Rect(initialPosition,
							enemySpriteVector.at(spriteIndex)->getWidth(),
							enemySpriteVector.at(spriteIndex)->getHeight()),
					life, points,
					new Animation(*enemyAnimationVector.at(spriteIndex)));
			int numOfSprites[1] = { 4 };
			toParse->addExplosionAnimation(
					new Animation("../gfx/EnemyExplosion.png", 500, 1,
							numOfSprites, 77, false));
			parseActions(enemyFile, toParse, enemySpriteVector,
					bulletSpriteVector, dropSpriteVector, enemyAnimationVector,
					target);
		} else if (strcasecmp(stringRead, "orbits") == 0) {
			parsedOrbits = parseOrbits(enemyFile, enemySpriteVector,
					bulletSpriteVector, dropSpriteVector, enemyAnimationVector,
					target, toParse);
		} else if (strcasecmp(stringRead, "drops") == 0) {
			parsedDrops = parseDrops(enemyFile, dropSpriteVector,
					bulletSpriteVector);
		} else if (strcasecmp(stringRead, "life") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%d", &life);
		} else if (strcasecmp(stringRead, "sprite") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%d", &spriteIndex);
		} else if (strcasecmp(stringRead, "points") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%d", &points);
		} else {
			fprintf(stderr, "%s: palavra nao reconhecida: '%s'.\n",
					fileName.c_str(), stringRead);
			exit(1);
		}
	}

	toParse->setBulletPatterns(parsedBulletPatterns);
	toParse->setOrbits(parsedOrbits);
	toParse->setDrops(parsedDrops);

	fclose(enemyFile);

	return toParse;
}

std::vector<BulletPattern*> EnemyParser::parsePatterns(FILE* fp,
		std::vector<Sprite*> bulletSpriteVector) {
	std::vector<BulletPattern*> toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {
		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {
			if (strcasecmp(stringRead, "pattern") == 0) {
				toReturn.push_back(parsePattern(fp, bulletSpriteVector));
			} else {
				fprintf(stderr,
						"parsePatterns: palavra nao reconhecida '%s', esperava 'pattern'.\n",
						stringRead);
				exit(1);
			}

			fscanf(fp, "%s", stringRead);
		}
	} else {
		fprintf(stderr, "parsePatterns: esperava 'begin', encontrou %s.\n",
				stringRead);
		exit(1);
	}

	return toReturn;

}

BulletPattern* EnemyParser::parsePattern(FILE* fp,
		std::vector<Sprite*> bulletSpriteVector) {
	BulletPattern* toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	int numShots;
	float shotVelocity;
	int waitInMillisecondsBetweenShots;
	int numRepeats;
	int spriteIndex;
	bool circular;

	if (strcasecmp(stringRead, "flower") == 0) {
		float angleBetweenBulletsInDegrees;
		bool clockwise;

		fscanf(fp, "%d %f %d %f %d", &numShots, &shotVelocity,
				&waitInMillisecondsBetweenShots, &angleBetweenBulletsInDegrees,
				&numRepeats);
		fscanf(fp, "%s", stringRead);
		clockwise = strcasecmp(stringRead, "clk") == 0;
		fscanf(fp, "%d", &spriteIndex);
		fscanf(fp, "%s", stringRead);
		circular = strstr(stringRead, "circ") != NULL;

		toReturn = new BulletPatternFlower(numShots, shotVelocity,
				waitInMillisecondsBetweenShots, angleBetweenBulletsInDegrees,
				numRepeats, clockwise, bulletSpriteVector.at(spriteIndex),
				circular);
	} else if (strcasecmp(stringRead, "spread") == 0) {
		float arcInDegrees;

		fscanf(fp, "%d %f %d %f %d", &numShots, &shotVelocity,
				&waitInMillisecondsBetweenShots, &arcInDegrees, &numRepeats);
		fscanf(fp, "%d", &spriteIndex);
		fscanf(fp, "%s", stringRead);
		circular = strstr(stringRead, "circ") != NULL;

		toReturn = new BulletPatternSpread(numShots, shotVelocity,
				waitInMillisecondsBetweenShots, arcInDegrees, numRepeats,
				bulletSpriteVector.at(spriteIndex), circular);

	} else if (strcasecmp(stringRead, "burst") == 0) {
		fscanf(fp, "%d %f %d %d", &numShots, &shotVelocity,
				&waitInMillisecondsBetweenShots, &numRepeats);
		fscanf(fp, "%d", &spriteIndex);
		fscanf(fp, "%s", stringRead);
		circular = strstr(stringRead, "circ") != NULL;

		toReturn = new BulletPatternBurst(numShots, shotVelocity,
				waitInMillisecondsBetweenShots, numRepeats,
				bulletSpriteVector.at(spriteIndex), circular);
	} else {
		fprintf(stderr, "Pattern nao reconhecido: %s.\n", stringRead);
		exit(1);
	}

	return toReturn;
}

void EnemyParser::parseActions(FILE* fp, Enemy* toParse,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target) {
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {
			if (strcasecmp(stringRead, "move") == 0) {
				float toMoveX;
				float toMoveY;
				float moveSpeed;

				fscanf(fp, "%f %f %f", &toMoveX, &toMoveY, &moveSpeed);

				toParse->AddAction(
						new EnemyMoveAction(Point(toMoveX, toMoveY), moveSpeed,
								toParse));
			} else if (strcasecmp(stringRead, "movestraight") == 0) {
				float toMoveY;
				float moveSpeed;

				fscanf(fp, "%f %f", &toMoveY, &moveSpeed);

				toParse->AddAction(
						new EnemyMoveStraightAction(toMoveY, moveSpeed,
								toParse));
			} else if (strcasecmp(stringRead, "shoot") == 0) {
				toParse->AddAction(new EnemyShootAction(toParse));
			} else if (strcasecmp(stringRead, "wait") == 0) {
				int waitInMilliseconds;

				fscanf(fp, "%d", &waitInMilliseconds);

				toParse->AddAction(
						new EnemyWaitAction(waitInMilliseconds, toParse));

			} else if (strcasecmp(stringRead, "stopshooting") == 0) {
				toParse->AddAction(new EnemyStopShootingAction(toParse));
			} else if (strcasecmp(stringRead, "add") == 0) {
				toParse->AddAction(
						new EnemyAddPatternAction(
								parsePattern(fp, bulletSpriteVector), toParse));
			} else if (strcasecmp(stringRead, "orbit") == 0) {
				toParse->AddAction(
						new EnemyAddOrbitAction(
								parseOrbit(fp, enemySpriteVector,
										bulletSpriteVector, dropSpriteVector,
										enemyAnimationVector, target, toParse),
								toParse));
			} else if (strcasecmp(stringRead, "die") == 0) {
				toParse->AddAction(new EnemyDieAction(toParse));
			} else {
				fprintf(stderr, "Action nao reconhecida: %s.\n", stringRead);
				exit(1);
			}

			fscanf(fp, "%s", stringRead);
		}
	} else {
		fprintf(stderr, "parseActions: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

}

std::vector<Enemy*> EnemyParser::parseOrbits(FILE* fp,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target,
		Enemy* orbitCenter) {
	std::vector<Enemy*> toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {
			if (strcasecmp(stringRead, "orbit") != 0) {
				fprintf(stderr,
						"Orbit parser: esperava 'orbit', encontrou '%s'.\n",
						stringRead);
				exit(1);
			}

			toReturn.push_back(
					parseOrbit(fp, enemySpriteVector, bulletSpriteVector,
							dropSpriteVector, enemyAnimationVector, target,
							orbitCenter));

			fscanf(fp, "%s", stringRead);

		}

	} else {
		fprintf(stderr, "Orbit parser: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

	return toReturn;
}

OrbitingEnemy* EnemyParser::parseOrbit(FILE* fp,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target,
		Enemy* orbitCenter) {
	OrbitingEnemy* toReturn;
	char stringRead[50];

	float initialAngle;
	float angularSpeed;
	float radius;
	bool clockwise;

	fscanf(fp, "%f %f %f", &initialAngle, &angularSpeed, &radius);
	fscanf(fp, "%s", stringRead);
	clockwise = strcasecmp(stringRead, "clk") == 0;
	fscanf(fp, "%s", stringRead);

	toReturn = new OrbitingEnemy(
			parseEnemy(stringRead, enemySpriteVector, bulletSpriteVector,
					dropSpriteVector, enemyAnimationVector, target),
			orbitCenter, initialAngle, angularSpeed, radius, clockwise);
	toReturn->setActionsOwnerAsSelf();
	int numOfSprites[1] = { 7 };
	toReturn->addExplosionAnimation(
			new Animation("../gfx/OrbitExplosion.png", 250, 1, numOfSprites, 79,
					false));

	return toReturn;
}

std::vector<Droppable*> EnemyParser::parseDrops(FILE* fp,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Sprite*> bulletSpriteVector) {

	std::vector<Droppable*> toReturn;
	Point initialPosition(0, -100);
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {

			Rect* dropHitbox = new Rect(initialPosition, 60, 47);

			if (strcasecmp(stringRead, "spread") == 0) {
				PlayerGunSpread* spreadGun;

				spreadGun = new PlayerGunSpread(1,
						bulletSpriteVector.at(SPREAD_BULLET_INDEX));

				toReturn.push_back(
						new DroppableWeapon(spreadGun, dropHitbox,
								dropSpriteVector.at(SPREAD_SPRITE_INDEX)));
			} else if (strcasecmp(stringRead, "laser") == 0) {
				PlayerGunLaser* laserGun;
				std::vector<Sprite*> laserBulletsSprites;

				laserBulletsSprites.push_back(
						bulletSpriteVector.at(LASER_LEVEL1_SPRITE_INDEX));
				laserBulletsSprites.push_back(
						bulletSpriteVector.at(LASER_LEVEL2_SPRITE_INDEX));
				laserBulletsSprites.push_back(
						bulletSpriteVector.at(LASER_LEVEL3_SPRITE_INDEX));

				laserGun = new PlayerGunLaser(laserBulletsSprites);

				toReturn.push_back(
						new DroppableWeapon(laserGun, dropHitbox,
								dropSpriteVector.at(LASER_SPRITE_INDEX)));
			} else if (strcasecmp(stringRead, "missile") == 0) {
				PlayerGunMissile* missileGun;

				missileGun = new PlayerGunMissile(1,
						bulletSpriteVector.at(MISSILE_BULLET_INDEX));

				toReturn.push_back(
						new DroppableWeapon(missileGun, dropHitbox,
								dropSpriteVector.at(MISSILE_SPRITE_INDEX)));
			} else if (strcasecmp(stringRead, "upgrade") == 0) {
				int numUpgradesToDrop;

				fscanf(fp, "%d", &numUpgradesToDrop);

				for (int i = 0; i < numUpgradesToDrop; i++) {
					toReturn.push_back(
							new DroppableUpgrade(dropHitbox,
									dropSpriteVector.at(UPGRADE_SPRITE_INDEX)));
					dropHitbox = new Rect(initialPosition, 60, 47);
				}

				delete (dropHitbox);

			} else if (strcasecmp(stringRead, "bomb") == 0) {
				toReturn.push_back(
						new DroppableBomb(dropHitbox,
								dropSpriteVector.at(BOMB_SPRITE_INDEX)));
			} else {
				fprintf(stderr, "Drop parser: palavra nao esperada: %s.\n",
						stringRead);
				exit(1);
			}

			fscanf(fp, "%s", stringRead);

		}

	} else {
		fprintf(stderr, "Drop parser: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

	return toReturn;

}
