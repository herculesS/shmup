/*
 * LabeledTextField.h
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#ifndef LABELEDTEXTFIELD_H_
#define LABELEDTEXTFIELD_H_

#include "Text.h"
#include "TextField.h"
#include "SDLBase.h"
#include "Point.h"
#include "Sprite.h"
#include <string>

#define HEIGHT_DIFFERENCE 30

class LabeledTextField {
private:
	Point position;
	Text* label;
	TextField* textField;

public:
	LabeledTextField(Point position, std::string label,
			std::string initialText);
	virtual ~LabeledTextField();

	void update();
	void render(float cameraX = 0, float cameraY = 0);

	std::string getTextFieldString() {
		return textField->getInputString();
	}
};

#endif /* LABELEDTEXTFIELD_H_ */
