/*
 * AnimationManager.h
 *
 *  Created on: Jul 11, 2013
 *      Author: Hercules
 */

#ifndef EXPLOSIONMANAGER_H_
#define EXPLOSIONMANAGER_H_

#include <vector>
#include "PositionedAnimation.h"
class AnimationManager {
private:
	static std::vector<PositionedAnimation*> animationVector;
public:
	static void update(double dt);
	static void render(float cameraX = 0, float cameraY = 0);
	static void cleanUp();
	static void instantiate(Point position, Animation* explosionAnimation);
};

#endif /* EXPLOSIONMANAGER_H_ */
