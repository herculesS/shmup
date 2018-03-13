/*
 * LabeledTextField.cpp
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#include "LabeledTextField.h"

LabeledTextField::LabeledTextField(Point position, std::string label,
		std::string initialText) {
	SDL_Color color;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	this->position = position;
	this->label = new Text("../ttf/Arial-Black.ttf", label, 14, 0, color,
			position.getX(), position.getY() - HEIGHT_DIFFERENCE);
	this->textField = new TextField(position, initialText);
}

LabeledTextField::~LabeledTextField() {
	delete (textField);
	delete (label);
}

void LabeledTextField::update() {
	textField->update();
}

void LabeledTextField::render(float cameraX, float cameraY) {
	textField->render(cameraX, cameraY);
	label->render(cameraX, cameraY, true);
}
