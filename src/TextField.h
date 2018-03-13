/*
 * TextField.h
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include "Text.h"
#include "Sprite.h"
#include "Point.h"
#include "InputManager.h"
#include <string>

class TextField {
private:
	Point position;
	SDL_Rect containerBox;
	Text* textToDisplay;
	Sprite* containerSprite;
	Sprite* highlightSprite;
	std::string inputString;

	bool active;
	bool highlighted;

public:
	TextField(Point position, std::string initialText = "");
	virtual ~TextField();

	void update();
	void render(float cameraX = 0, float cameraY = 0);

	std::string getInputString() {
		return inputString;
	}
};

#endif /* TEXTFIELD_H_ */
