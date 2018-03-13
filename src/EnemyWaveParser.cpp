/*
 * EnemyWaveParser.cpp
 *
 *  Created on: 11/07/2013
 *      Author: vitor
 */

#include "EnemyWaveParser.h"

EnemyWave* EnemyWaveParser::parseEnemyWave(std::string fileName,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target) {

	char stringRead[50];
	FILE* enemyWaveFile;
	EnemyWave* toReturn;

	toReturn = new EnemyWave();

	if ((enemyWaveFile = fopen(fileName.c_str(), "r")) == NULL) {
		fprintf(stderr, "Wave parser: nao consegui abrir o arquivo %s.\n",
				fileName.c_str());
		exit(1);
	}

	fscanf(enemyWaveFile, "%s", stringRead);

	if (strcasecmp(stringRead, "wave") == 0) {

		fscanf(enemyWaveFile, "%s", stringRead);

		if (strcasecmp(stringRead, "begin") == 0) {

			fscanf(enemyWaveFile, "%s", stringRead);

			while (strcasecmp(stringRead, "end") != 0) {
				int startTimeInMilliseconds;
				float initialX;
				float initialY;
				std::string enemyFileName(stringRead);
				Enemy* enemy;

				fscanf(enemyWaveFile, "%f %f %d", &initialX, &initialY,
						&startTimeInMilliseconds);

				enemy = EnemyParser::parseEnemy(enemyFileName,
						enemySpriteVector, bulletSpriteVector, dropSpriteVector,
						enemyAnimationVector, target);
				enemy->getShape()->setCenter(Point(initialX, initialY));

				toReturn->AddEnemy(enemy, startTimeInMilliseconds);

				fscanf(enemyWaveFile, "%s", stringRead);
			}

		} else {
			fprintf(stderr,
					"Wave parser: %s: esperava 'begin', encontrou '%s'.\n",
					fileName.c_str(), stringRead);
			exit(1);
		}

	} else {
		fprintf(stderr, "Wave parser: %s: esperava 'wave', encontrou '%s'.\n",
				fileName.c_str(), stringRead);
		exit(1);
	}

	fclose(enemyWaveFile);

	return toReturn;

}
