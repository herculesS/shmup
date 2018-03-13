/*
 * DropManager.h
 *
 *  Created on: 09/07/2013
 *      Author: Vitor
 */

#ifndef DROPMANAGER_H_
#define DROPMANAGER_H_

#include "Droppable.h"
#include "CollisionManager.h"
#include <vector>

class Droppable;
class DropManager {
private:
	static std::vector<Droppable*> dropVector;

	static bool valueInRange(float value, float min, float max);

public:
	static void update(double dt);
	static void render(float cameraX = 0, float cameraY = 0);
	static void cleanUp();
	static void insertDrops(std::vector<Droppable*> toInsert);
	static void removeOffScreenDrops(float areaWidth, float areaHeight);
	static Droppable* checkCollision(GameObject* toCollide);
};

#endif /* DROPMANAGER_H_ */
