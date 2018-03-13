/*
 * ExplosionManager.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Hercules
 */

#include "AnimationManager.h"
std::vector<PositionedAnimation*> AnimationManager::animationVector;

void AnimationManager::update(double dt) {
	for (std::vector<PositionedAnimation*>::iterator it =
			animationVector.begin(); it != animationVector.end(); it++) {
		(*it)->update(dt);
		if ((*it)->ended()) {
			delete (*it);
			it = animationVector.erase(it);
			it--;
		}
	}
}
void AnimationManager::render(float cameraX, float cameraY) {
	for (std::vector<PositionedAnimation*>::iterator it =
			animationVector.begin(); it != animationVector.end(); it++) {
		(*it)->render();
	}
}
void AnimationManager::cleanUp() {
	for (std::vector<PositionedAnimation*>::iterator it =
			animationVector.begin(); it != animationVector.end(); it++) {
		delete (*it);
		it = animationVector.erase(it);
		it--;
	}
}
void AnimationManager::instantiate(Point position,
		Animation* explosionAnimation) {
	animationVector.push_back(
			new PositionedAnimation(position, explosionAnimation));
}
