/*
 * StageParser.h
 *
 *  Created on: 13/07/2013
 *      Author: vitor
 */

#ifndef STAGEPARSER_H_
#define STAGEPARSER_H_

#include "EnemyWaveParser.h"
#include "Stage.h"

class StageParser {
public:
	static Stage* parseStage(std::string fileName,
			std::vector<Sprite*> backgroundSprites,
			std::vector<Sprite*> enemySpriteVector,
			std::vector<Sprite*> bulletSpriteVector,
			std::vector<Sprite*> dropSpriteVector,
			std::vector<Animation*> enemyAnimationVector, GameObject* target);
};

#endif /* STAGEPARSER_H_ */
