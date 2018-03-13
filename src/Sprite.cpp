/*
 * Sprite.cpp
 *
 *  Created on: 06/04/2013
 *      Author: Vitor
 */

#include "Sprite.h"

using namespace std;

Sprite::Sprite(string fileName) {

	spriteSurface = NULL;
	rotoZoomSurface = NULL;

	scaleX = scaleY = 1;
	angle = 0;

	hidden = false;

	load(fileName);

}

Sprite::~Sprite() {
	if (spriteSurface) {
		SDL_FreeSurface(spriteSurface);
	}
	if (rotoZoomSurface) {
		SDL_FreeSurface(rotoZoomSurface);
	}
}

void Sprite::update(int dt) {
}

void Sprite::rotoZoom(float angle, float scaleX, float scaleY, bool force) {

	if (scaleX != this->scaleX || scaleY != this->scaleY || angle != this->angle
			|| force) {
		if (rotoZoomSurface != NULL) {
			SDL_FreeSurface(rotoZoomSurface);
		}

		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->angle = angle;

		if (clipRect.x != 0 || clipRect.y != 0 || clipRect.w != spriteSurface->w
				|| clipRect.h != spriteSurface->h) {

			SDL_Rect clipRectCopy = clipRect;

			rotoZoomSurface = SDLBase::clip(spriteSurface, &clipRectCopy);
			rotoZoomSurface = SDLBase::rotoZoom(rotoZoomSurface, angle, scaleX,
					scaleY);

		} else {
			rotoZoomSurface = SDLBase::rotoZoom(spriteSurface, angle, scaleX,
					scaleY);
		}
	}

}

void Sprite::restore() {
	if (rotoZoomSurface != NULL) {
		SDL_FreeSurface(rotoZoomSurface);
	}
}

void Sprite::load(std::string fileName) {
	if (spriteSurface != NULL) {
		SDL_FreeSurface(spriteSurface);
	}

	spriteSurface = SDLBase::loadImage(fileName);

	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = spriteSurface->w;
	clipRect.h = spriteSurface->h;
}

void Sprite::clip(int x, int y, int w, int h) {

	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;

	if (rotoZoomSurface != NULL) {
		rotoZoom(this->angle, this->scaleX, this->scaleY, true);
	}

}

SDL_Rect Sprite::getClip() {
	return clipRect;
}

int Sprite::getWidth() {
	return rotoZoomSurface ? rotoZoomSurface->w : spriteSurface->w;
}

int Sprite::getHeight() {
	return rotoZoomSurface ? rotoZoomSurface->h : spriteSurface->h;
}

void Sprite::render(int x, int y, bool center, SDL_Surface *destSurf) {

	SDL_Rect tempRect;
	SDL_Surface* toRender;

	if (!hidden) {
		if (rotoZoomSurface) {
			toRender = rotoZoomSurface;

			if (!center) {
				x += (clipRect.w / 2 - rotoZoomSurface->w / 2);
				y += (clipRect.h / 2 - rotoZoomSurface->h / 2);
			} else {
				x -= rotoZoomSurface->w / 2;
				y -= rotoZoomSurface->h / 2;
			}
		} else {
			toRender = spriteSurface;

			if (center) {
				x -= clipRect.w / 2;
				y -= clipRect.h / 2;
			}
		}

		tempRect.x = x;
		tempRect.y = y;
		if (!destSurf) {
			SDLBase::renderSurface(toRender, rotoZoomSurface ? 0 : &clipRect,
					&tempRect);
		} else {
			if (SDL_BlitSurface(toRender, rotoZoomSurface ? 0 : &clipRect,
					destSurf, &tempRect) == -1) {
				fprintf(stderr,
						"Nao consegui blitar uma surface de dimensoes: %dx%d",
						clipRect.w, clipRect.h);
				exit(1);
			}
		}
	}

}

