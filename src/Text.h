/*
 * Text.h
 *
 *  Created on: 04/06/2013
 *      Author: vitor
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "SDLBase.h"
#include "Point.h"
#include <string>

class Text {
private:
	TTF_Font* font;
	SDL_Surface* textSurface;
	std::string fontFileName;
	std::string text;
	int style;
	int ptSize;
	SDL_Color color;
	Point position;

public:
	Text(std::string fontFileName, std::string text, int ptSize, int style,
			SDL_Color color, int x, int y);
	virtual ~Text();
	void render(float cameraX, float cameraY, bool center, SDL_Surface* dst =
			NULL);
	int getWidth() {
		return textSurface->w;
	}
	int getHeight() {
		return textSurface->h;
	}
	Point* getPos() {
		return &position;
	}
	void setPos(int x, int y);
	void setText(std::string text);
	void setStyle(int style);
	void setColor(SDL_Color color);
	void setSize(int ptSize);

};

#endif /* TEXT_H_ */
