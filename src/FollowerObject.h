/*
 * FollowerObject.h
 *
 *  Created on: 26/05/2013
 *      Author: Vitor
 */

#ifndef FOLLOWEROBJECT_H_
#define FOLLOWEROBJECT_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"
#include <queue>

class FollowerObject: public GameObject {
private:
	Sprite* sprite;
	Vector2 speed;
	std::queue<Point> coordinatesQueue;

public:
	FollowerObject(Sprite* sprite, Shape* shape);
	virtual ~FollowerObject();

	int update(double dt);
	void render(float cameraX, float cameraY);
	void renderQueueLines(float cameraX, float cameraY);
	void enqueueCommand(Point position);
};

#endif /* FOLLOWEROBJECT_H_ */
