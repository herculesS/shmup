/*
 * Button.h
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "SDLBase.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Point.h"

class Button {
private:
	SDL_Rect buttonRect;
	Sprite* buttonSprite;
	Sprite* buttonImageSprite;
	Point position;

	bool clicked;

public:
	Button(Point position, Sprite* buttonSprite, Sprite* buttonImageSprite);
	virtual ~Button();

	void update();
	void render(float cameraX = 0, float cameraY = 0);

	bool isClicked() const {
		return clicked;
	}

	const Point& getPosition() const {
		return position;
	}

	void setPosition(const Point& position) {
		this->position = position;
		buttonRect.x = position.getX() - buttonSprite->getWidth() / 2;
		buttonRect.y = position.getY() - buttonSprite->getHeight() / 2;
	}
};

#endif /* BUTTON_H_ */
