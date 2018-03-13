/*
 * SDLBase.h
 *
 *  Created on: 06/04/2013
 *      Author: Vitor
 */

#ifndef SDLBASE_H_
#define SDLBASE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <string>

class SDLBase {

private:
	static SDL_Surface* screen;

public:

	enum {
		STATENOCHANGE = 0,
		STATESPLASH,
		STATEGAME,
		STATEWIN,
		STATELOSE,
		STATEQUIT,
		STATEDESTROY,
		STATEEDITOR,
		STATEPAUSE,
		STATEMENU
	};

	static int inicializaSDL();

	static void finalizaSDL();

	static SDL_Surface* getScreen();

	static SDL_Surface* loadImage(std::string fileName);

	static SDL_Surface* clip(SDL_Surface* original, SDL_Rect* clip);

	static SDL_Surface* rotoZoom(SDL_Surface* surface, float angle,
			float scaleX, float scaleY);

	static void renderSurface(SDL_Surface* surface, SDL_Rect* clip,
			SDL_Rect* dst);

	static void drawLine(int x1, int y1, int x2, int y2, int rgb, int spacing);

	static void atualizarTela();

};

#endif /* SDLBASE_H_ */
