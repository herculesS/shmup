/*
 * Stage.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Hercules
 */

#ifndef STAGE_H_
#define STAGE_H_
#include "EnemyWave.h"
#include "Sprite.h"
#include "GameArea.h"
#include <queue>
#include <deque>
#include <vector>

class Stage {
private:
	std::queue<EnemyWave*, std::deque<EnemyWave*> > wavesQueue;
	std::vector<Sprite*> backgroundSprites;

	int wavesFinished;
	int killedEnemies;

	Vector2 backgroundSpeed;
	Point backgroundPosition;

	Sprite* mainGameAreaBackground;
	Sprite* auxGameAreaBackground;
	Sprite* transitionGameAreaBackground;
	bool started;
	bool transitioning;
	bool transitionStarted;
	int transitionCounter;

	struct transition {
		int transitionWave;
		int transitionSprite;
		int loopSprite[3];
	};
	std::queue<struct transition> transitionQueue;

	void updateBackground(double dt);

public:
	Stage(std::vector<Sprite*> backgroundSprites);
	void update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void renderBackground(float cameraX = 0, float cameraY = 0);
	void start();
	void addWave(EnemyWave* toAdd);
	void addTransition(int transitionWave, int transitionSpriteIndex,
			int* loopSpriteIndexes);
	void checkCollision(float areaWidth, float areaHeight);
	Point* getClosestEnemyPosition(Point* toCheck, float areaWidth,
			float areaHeight);
	virtual ~Stage();
	bool isFineshed();
	int getKilledEnemies() {
		return killedEnemies;
	}
};

#endif /* STAGE_H_ */
