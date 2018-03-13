/*
 * Text.cpp
 *
 *  Created on: 04/06/2013
 *      Author: vitor
 */

#include "Text.h"

Text::Text(std::string fontFileName, std::string text, int ptSize, int style,
		SDL_Color color, int x, int y) {
	this->fontFileName = fontFileName;
	this->text = text;
	this->ptSize = ptSize;
	this->style = style;
	this->color = color;
	this->position.setX(x);
	this->position.setY(y);

	font = TTF_OpenFont(fontFileName.c_str(), ptSize);

	if (!font)
		fprintf(stderr, "Nao consegui abrir a fonte no caminho: %s.\n",
				fontFileName.c_str());

	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (!textSurface && !text.empty())
		fprintf(stderr,
				"Nao consegui carregar o seguinte texto numa surface: %s.\n",
				text.c_str());

}

Text::~Text() {
	TTF_CloseFont(font);
	SDL_FreeSurface(textSurface);
}

void Text::render(float cameraX, float cameraY, bool center, SDL_Surface* dst) {

	SDL_Rect posRect;

	if (textSurface) {
		posRect.x = position.getX() - cameraX;
		posRect.y = position.getY() - cameraY;

		if (center) {
			posRect.x -= textSurface->w / 2;
			posRect.y -= textSurface->h / 2;
		}
		if (!dst) {
			SDLBase::renderSurface(textSurface, NULL, &posRect);
		} else {
			if (SDL_BlitSurface(textSurface, NULL, dst, &posRect) == -1) {
				fprintf(stderr, "Nao consegui blitar surface");
				exit(1);
			}
		}
	}
}

void Text::setPos(int x, int y) {
	this->position.setX(x);
	this->position.setY(y);
}

void Text::setText(std::string text) {
	SDL_FreeSurface(textSurface);
	this->text = text;
	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

void Text::setStyle(int style) {
	SDL_FreeSurface(textSurface);
	this->style = style;
	TTF_SetFontStyle(font, style);
	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

void Text::setColor(SDL_Color color) {
	SDL_FreeSurface(textSurface);
	this->color = color;
	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

void Text::setSize(int ptSize) {
	SDL_FreeSurface(textSurface);
	this->ptSize = ptSize;
	TTF_CloseFont(font);
	font = TTF_OpenFont(fontFileName.c_str(), ptSize);
	TTF_SetFontStyle(font, style);
	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}
