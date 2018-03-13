/*
 * abc.cpp
 *
 *  Created on: 06/04/2013
 *      Author: Vitor
 */

#include "SDLBase.h"

SDL_Surface* SDLBase::screen;

int SDLBase::inicializaSDL() {

	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);

	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);

	TTF_Init();
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
			MIX_DEFAULT_CHANNELS, 1024);

	if (screen == NULL) {
		fprintf(stderr, "Nao consegui carregar a tela\n");
		exit(1);
	}

	SDL_WM_SetCaption("Projeto IDJ - Shmup", "Projeto IDJ - Shmup");

	return 0;

}

void SDLBase::finalizaSDL() {
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

SDL_Surface* SDLBase::getScreen() {
	return screen;
}

SDL_Surface* SDLBase::loadImage(std::string fileName) {

	SDL_Surface* surface = 0;
	SDL_Surface* surfAux = 0;

	surface = IMG_Load(fileName.c_str());

	if (surface == NULL) {
		fprintf(stderr, "Nao consegui carregar a imagem no caminho %s\n",
				fileName.c_str());
		exit(1);
	}

	// A surface possui transpar�ncia alfa?
	if (surface->format->Amask != 0) {
		surfAux = SDL_DisplayFormatAlpha(surface);
	} else {
		surfAux = SDL_DisplayFormat(surface);
	}

	SDL_FreeSurface(surface);

	return surfAux;

}

SDL_Surface* SDLBase::clip(SDL_Surface* original, SDL_Rect* clip) {

	SDL_Surface* surfAux;

	if (original == NULL || clip == NULL) {
		fprintf(stderr,
				"Erro na funcao SDLBase::clip: surface ou clip estao NULL.\n");
		exit(1);
	}

	surfAux = SDL_CreateRGBSurface(original->flags, clip->w, clip->h,
			screen->format->BitsPerPixel, 0, 0, 0, 0);

	SDL_BlitSurface(original, clip, surfAux, NULL);

	return surfAux;

}

SDL_Surface* SDLBase::rotoZoom(SDL_Surface* surface, float angle, float scaleX,
		float scaleY) {

	if (surface == NULL || scaleX < 0 || scaleY < 0) {
		fprintf(stderr,
				"Erro na funcao SDLBase::rotozoom: surface esta NULL ou alguma escala foi passada como negativo.\n");
		exit(1);
	}

	return rotozoomSurfaceXY(surface, angle, scaleX, scaleY, 1);
}

void SDLBase::drawLine(int x1, int y1, int x2, int y2, int rgb, int spacing) {
	int deltax = abs(x2 - x1); // The difference between the x's
	int deltay = abs(y2 - y1); // The difference between the y's
	int x = x1;                // Start x off at the first pixel
	int y = y1;                // Start y off at the first pixel
	int xinc1 = 0;
	int yinc1 = 0;
	int xinc2 = 0;
	int yinc2 = 0;
	int den = 0;
	int num = 0;
	int numadd = 0;
	int numpixels = 0;

	if (x2 >= x1)              // The x-values are increasing
			{
		xinc1 = 1;
		xinc2 = 1;
	} else                       // The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)              // The y-values are increasing
			{
		yinc1 = 1;
		yinc2 = 1;
	} else                       // The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)	// There is at least one x-value for every y-value
			{
		xinc1 = 0;			// Don't change the x when numerator >= denominator
		yinc2 = 0;				// Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;		// There are more x-values than y-values
	} else					// There is at least one y-value for every x-value
	{
		xinc2 = 0;				// Don't change the x for every iteration
		yinc1 = 0;			// Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;		// There are more y-values than x-values
	}

	for (int curpixel = 1; curpixel <= numpixels; curpixel++) {
		if (spacing == 0) {
			SDL_Rect pixel = { (short) x, (short) y, 1, 1 };
			SDL_FillRect(screen, &pixel, rgb);
		} else if (curpixel % spacing >= spacing / 2) {
			SDL_Rect pixel = { (short) x, (short) y, 1, 1 };
			SDL_FillRect(screen, &pixel, rgb);
		}

		num += numadd;      // Increase the numerator by the top of the fraction
		if (num >= den)        // Check if numerator >= denominator
				{
			num -= den;         // Calculate the new numerator value
			x += xinc1;         // Change the x as appropriate
			y += yinc1;         // Change the y as appropriate
		}
		x += xinc2;             // Change the x as appropriate
		y += yinc2;             // Change the y as appropriate
	}
}

void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect* clip,
		SDL_Rect* dst) {

	if (SDL_BlitSurface(surface, clip, screen, dst) == -1) {
		fprintf(stderr, "Nao consegui blitar uma surface de dimensoes: %dx%d",
				clip->w, clip->h);
		exit(1);
	}

}

void SDLBase::atualizarTela() {
	SDL_Flip(screen);
}

