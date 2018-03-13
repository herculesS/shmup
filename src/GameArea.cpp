/*
 * GameArea.cpp
 *
 *  Created on: Jun 19, 2013
 *      Author: AT WORK
 */

#include "GameArea.h"

SDL_Surface* GameArea::surface = NULL;
Point* GameArea::Position = NULL;
Rect * GameArea::MultArea8X = NULL;
Rect * GameArea::MultArea4X = NULL;
Rect * GameArea::MultArea2X = NULL;
Rect * GameArea::MultArea1X = NULL;

GameArea::~GameArea() {
	// TODO Auto-generated destructor stub
}
void GameArea::render() {
	SDL_Rect dst;
	dst.w = dst.h = 0;
	dst.x = Position->getX();
	dst.y = Position->getY();
	SDLBase::renderSurface(surface, NULL, &dst);
}

void GameArea::inicialize() {
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, GAME_AREA_WIDTH,
			GAME_AREA_HEIGHT, SDLBase::getScreen()->format->BitsPerPixel, 0, 0,
			0, 0);
	Position = new Point(200, 0);
	MultArea8X = new Rect(GAME_AREA_WIDTH / 2, 57, GAME_AREA_WIDTH, 115);
	MultArea4X = new Rect(GAME_AREA_WIDTH / 2, 185, GAME_AREA_WIDTH, 140);
	MultArea2X = new Rect(GAME_AREA_WIDTH / 2, 325, GAME_AREA_WIDTH, 140);
	MultArea1X = new Rect(GAME_AREA_WIDTH / 2, 497, GAME_AREA_WIDTH, 205);
}

void GameArea::finalize() {
	SDL_FreeSurface(surface);
	delete (Position);
	delete (MultArea1X);
	delete (MultArea2X);
	delete (MultArea4X);
	delete (MultArea8X);
}

void GameArea::update(int dt) {
	SDL_Flip(surface);
}
int GameArea::getMultiplier(Shape* other) {
	if (CollisionManager::checkCollision(MultArea1X, other)) {
		return 1;
	}
	if (CollisionManager::checkCollision(MultArea2X, other)) {
		return 2;
	}
	if (CollisionManager::checkCollision(MultArea4X, other)) {
		return 4;
	}
	if (CollisionManager::checkCollision(MultArea8X, other)) {
		return 8;
	}

	return 0;
}
