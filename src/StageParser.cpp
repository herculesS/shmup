/*
 * StageParser.cpp
 *
 *  Created on: 13/07/2013
 *      Author: vitor
 */

#include "StageParser.h"

Stage* StageParser::parseStage(std::string fileName,
		std::vector<Sprite*> backgroundSprites,
		std::vector<Sprite*> enemySpriteVector,
		std::vector<Sprite*> bulletSpriteVector,
		std::vector<Sprite*> dropSpriteVector,
		std::vector<Animation*> enemyAnimationVector, GameObject* target) {

	Stage* toReturn;
	char stringRead[50];
	FILE* stageFile;
	int waveCounter = 0;

	toReturn = new Stage(backgroundSprites);

	if ((stageFile = fopen(fileName.c_str(), "r")) == NULL) {
		fprintf(stderr, "Stage parser: Nao consegui abrir o arquivo %s.\n",
				fileName.c_str());
		exit(1);
	}

	fscanf(stageFile, "%s", stringRead);

	if (strcasecmp(stringRead, "stage") == 0) {

		fscanf(stageFile, "%s", stringRead);

		if (strcasecmp(stringRead, "begin") == 0) {

			fscanf(stageFile, "%s", stringRead);

			while (strcasecmp(stringRead, "end") != 0) {

				if (strcasecmp("transition", stringRead) == 0) {
					int transitionSpriteIndex;
					int loopSpriteIndexes[3];

					fscanf(stageFile, "%d %d %d %d", &transitionSpriteIndex,
							&loopSpriteIndexes[0], &loopSpriteIndexes[1],
							&loopSpriteIndexes[2]);

					toReturn->addTransition(waveCounter, transitionSpriteIndex,
							loopSpriteIndexes);
				} else {
					toReturn->addWave(
							EnemyWaveParser::parseEnemyWave(
									std::string(stringRead), enemySpriteVector,
									bulletSpriteVector, dropSpriteVector,
									enemyAnimationVector, target));

					waveCounter++;
				}

				fscanf(stageFile, "%s", stringRead);
			}

		} else {
			fprintf(stderr,
					"Stage parser: %s: esperava 'begin', encontrou '%s'.\n",
					fileName.c_str(), stringRead);
			exit(1);
		}

	} else {
		fprintf(stderr, "Stage parser: %s: esperava 'stage', encontrou '%s'.\n",
				fileName.c_str(), stringRead);
		exit(1);
	}

	fclose(stageFile);

	return toReturn;

}
