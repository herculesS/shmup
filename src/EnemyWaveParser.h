/*
 * EnemyWaveParser.h
 *
 *  Created on: 11/07/2013
 *      Author: vitor
 */

#ifndef ENEMYWAVEPARSER_H_
#define ENEMYWAVEPARSER_H_

#include "EnemyParser.h"
#include "EnemyWave.h"
#include <string>

class EnemyWaveParser {
public:
	static EnemyWave* parseEnemyWave(std::string fileName,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target);
};

#endif /* ENEMYWAVEPARSER_H_ */
