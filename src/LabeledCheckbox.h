/*
 * LabeledCheckbox.h
 *
 *  Created on: 24/07/2013
 *      Author: vitor
 */

#ifndef LABELEDCHECKBOX_H_
#define LABELEDCHECKBOX_H_

#include "Checkbox.h"
#include "Text.h"
#include "Point.h"
#include <string>

#define HEIGHT_DIFFERENCE 30

class LabeledCheckbox {
private:
	Point position;
	Text* label;
	Checkbox* checkbox;

public:
	LabeledCheckbox(Point position, std::string label, bool selected);
	virtual ~LabeledCheckbox();

	void update();
	void render(float cameraX = 0, float cameraY = 0);
	bool isSelected() {
		return checkbox->isSelected();
	}
};

#endif /* LABELEDCHECKBOX_H_ */
