/*
 * Stage.cpp
 *
 *  Created on: Jul 13, 2013
 *      Author: Hercules
 */

#include "Stage.h"

Stage::Stage(std::vector<Sprite*> backgroundSprites) {
	started = false;
	transitioning = false;
	transitionStarted = false;
	wavesFinished = 0;
	transitionCounter = 0;

	this->backgroundSprites = backgroundSprites;

	mainGameAreaBackground = backgroundSprites.at(0);
	auxGameAreaBackground = backgroundSprites.at(0);
	transitionGameAreaBackground = backgroundSprites.at(0);

	killedEnemies = 0;
}

void Stage::start() {
	started = true;
	if (!wavesQueue.empty()) {
		wavesQueue.front()->start();
	}

	backgroundPosition.setX(0);
	backgroundPosition.setY(
			GAME_AREA_HEIGHT - mainGameAreaBackground->getHeight());
	backgroundSpeed.setX(0);
	backgroundSpeed.setY(80);
}

void Stage::update(double dt) {
	if (started) {
		if (!wavesQueue.empty()) {
			wavesQueue.front()->update(dt);
			if (wavesQueue.front()->isFinished()) {
				killedEnemies += wavesQueue.front()->getNumOfKilledEnemies();
				delete (wavesQueue.front());
				wavesQueue.pop();
				if (!wavesQueue.empty()) {
					wavesQueue.front()->start();
				}

				wavesFinished++;
			}
		}

		updateBackground(dt);
	}
}

void Stage::updateBackground(double dt) {
	// Movimento dos backgrounds
	backgroundPosition = backgroundPosition.addVector(
			backgroundSpeed.constantProduct(dt));

	// Primeiro vemos se devemos começar a transição
	if (!transitionQueue.empty()
			&& wavesFinished >= transitionQueue.front().transitionWave) {
		transitioning = true;
	}

	// Se a transição tiver acabado de começar,
	// devemos trocar o sprite de transição para o adequado.
	if (transitioning) {
		if (!transitionStarted) {
			transitionGameAreaBackground = backgroundSprites.at(
					transitionQueue.front().transitionSprite);
			transitionStarted = true;
		}
	}

	// Checagem para mover o main background para o fim da "pilha" de backgrounds
	if (backgroundPosition.getY() >= GAME_AREA_HEIGHT) {
		Sprite* aux;

		backgroundPosition.setY(
				backgroundPosition.getY()
						- mainGameAreaBackground->getHeight());

		if (transitioning) {
			aux = backgroundSprites.at(
					transitionQueue.front().loopSprite[transitionCounter]);
			transitionCounter++;
		} else {
			aux = mainGameAreaBackground;
		}
		mainGameAreaBackground = auxGameAreaBackground;
		auxGameAreaBackground = transitionGameAreaBackground;
		transitionGameAreaBackground = aux;
	}

	if (transitionCounter >= 3) {
		transitioning = false;
		transitionStarted = false;
		transitionCounter = 0;
		transitionQueue.pop();
	}
}

void Stage::render(float cameraX, float cameraY) {
	if (started) {
		if (!wavesQueue.empty()) {
			wavesQueue.front()->render(cameraX, cameraY);
		}
	}
}

void Stage::renderBackground(float cameraX, float cameraY) {
	// Render dos backgrounds
	mainGameAreaBackground->render(backgroundPosition.getX(),
			backgroundPosition.getY(), 0, GameArea::getSurface());
	auxGameAreaBackground->render(backgroundPosition.getX(),
			backgroundPosition.getY() - mainGameAreaBackground->getHeight(), 0,
			GameArea::getSurface());
	transitionGameAreaBackground->render(backgroundPosition.getX(),
			backgroundPosition.getY() - mainGameAreaBackground->getHeight()
					- auxGameAreaBackground->getHeight(), 0,
			GameArea::getSurface());
}

void Stage::addTransition(int transitionWave, int transitionSpriteIndex,
		int* loopSpriteIndexes) {
	struct transition toAdd;

	toAdd.transitionWave = transitionWave;
	toAdd.transitionSprite = transitionSpriteIndex;
	toAdd.loopSprite[0] = loopSpriteIndexes[0];
	toAdd.loopSprite[1] = loopSpriteIndexes[1];
	toAdd.loopSprite[2] = loopSpriteIndexes[2];

	transitionQueue.push(toAdd);
}

void Stage::addWave(EnemyWave* toAdd) {
	wavesQueue.push(toAdd);
}

Point* Stage::getClosestEnemyPosition(Point* toCheck, float areaWidth,
		float areaHeight) {
	if (wavesQueue.empty()) {
		return NULL;
	}

	Point* toReturn;
	toReturn = wavesQueue.front()->getClosestEnemyPosition(toCheck, areaWidth,
			areaHeight);
	return toReturn;
}

void Stage::checkCollision(float areaWidth, float areaHeight) {
	if (!wavesQueue.empty()) {
		wavesQueue.front()->checkCollision(areaWidth, areaHeight);
	}
}
bool Stage::isFineshed() {
	if (wavesQueue.empty()) {
		return true;
	}
	return false;
}
Stage::~Stage() {
	while (!wavesQueue.empty()) {
		delete (wavesQueue.front());
		wavesQueue.pop();
	}
}

