/*
 * Sprite.h
 *
 *  Created on: 06/04/2013
 *      Author: Vitor
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDLBase.h"

class Sprite {
protected:
	SDL_Surface* spriteSurface;
	SDL_Surface* rotoZoomSurface;
	SDL_Rect clipRect;

	float angle;
	float scaleX, scaleY;
	bool hidden;

public:
	Sprite(std::string fileName);
	virtual ~Sprite();

	virtual void update(int dt);

	void rotoZoom(float angle, float scaleX, float scaleY, bool force);

	void restore();

	void load(std::string fileName);

	void clip(int x, int y, int w, int h);

	SDL_Rect getClip();

	int getWidth();

	int getHeight();

	virtual void render(int x, int y, bool center, SDL_Surface *destSurf =
			SDLBase::getScreen());

	void setHidden(bool hidden) {
		this->hidden = hidden;
	}
};

#endif /* SPRITE_H_ */
