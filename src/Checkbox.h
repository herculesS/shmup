/*
 * Checkbox.h
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include "Sprite.h"
#include "InputManager.h"
#include "Point.h"

class Checkbox {
private:
	Point position;
	Sprite* selectedSprite;
	Sprite* checkBoxContainerSprite;

	SDL_Rect containerBox;

	bool selected;

public:
	Checkbox(Point position, bool selected);
	virtual ~Checkbox();

	void update();
	void render(float cameraX = 0, float cameraY = 0);

	bool isSelected() const {
		return selected;
	}
};

#endif /* CHECKBOX_H_ */
