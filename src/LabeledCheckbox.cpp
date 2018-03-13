/*
 * LabeledCheckbox.cpp
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#include "LabeledCheckbox.h"

LabeledCheckbox::LabeledCheckbox(Point position, std::string label,
		bool selected) {

	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	this->position = position;
	this->label = new Text("../ttf/Arial-Black.ttf", label, 14, 0, color,
			position.getX(), position.getY() - HEIGHT_DIFFERENCE);
	this->checkbox = new Checkbox(position, selected);
}

LabeledCheckbox::~LabeledCheckbox() {
	delete (label);
	delete (checkbox);
}

void LabeledCheckbox::update() {
	checkbox->update();
}

void LabeledCheckbox::render(float cameraX, float cameraY) {
	label->render(cameraX, cameraY, true);
	checkbox->render(cameraX, cameraY);
}
