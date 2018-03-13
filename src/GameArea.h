/*
 * GameArea.h
 *
 *  Created on: Jun 19, 2013
 *      Author: AT WORK
 */

#ifndef GAMEAREA_H_
#define GAMEAREA_H_
#include "SDLBase.h"
#include "Point.h"
#include "Rect.h"
#include "CollisionManager.h"
#define GAME_AREA_WIDTH 600
#define GAME_AREA_HEIGHT 600

class GameArea {
private:
	static SDL_Surface *surface;
	static Point *Position;
	static Rect* MultArea8X;
	static Rect* MultArea4X;
	static Rect* MultArea2X;
	static Rect* MultArea1X;
public:
	static void inicialize();
	static void finalize();
	virtual ~GameArea();
	static void render();
	static void update(int dt);
	static SDL_Surface *getSurface() {
		return surface;
	}
	static Point* getPosition() {
		return Position;
	}
	static int getMultiplier(Shape* other);
};

#endif /* GAMEAREA_H_ */
