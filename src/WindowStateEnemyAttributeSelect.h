/*
 * WindowStateEnemyAttributeSelect.h
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATEENEMYATTRIBUTESELECT_H_
#define WINDOWSTATEENEMYATTRIBUTESELECT_H_

#include "WindowState.h"
#include "StateArgs.h"
#include "LabeledTextField.h"
#include <string>
#include <string.h>
#include <vector>

#define SUBTITLE_X 400
#define SUBTITLE_Y 50

#define SAVE_FILE_X 770
#define SAVE_FILE_Y 250

#define ATTRIBUTE_BASE_X 280
#define ATTRIBUTE_BASE_Y 350
#define ATTRIBUTE_OFFSET 80

class WindowStateEnemyAttributeSelect: public WindowState {
private:
	std::string enemyFileName;
	Text* subTitle;

	LabeledTextField* lifeTextField;
	LabeledTextField* spriteIndexTextField;
	LabeledTextField* pointsTextField;

	std::vector<std::vector<std::string> > dropsVector;
	std::vector<std::vector<std::string> > orbitsVector;
	std::vector<std::vector<std::string> > actionsVector;
	std::vector<std::vector<std::string> > patternsVector;

	bool accessingDrops;
	bool accessingOrbits;
	bool accessingActions;
	bool accessingPatterns;

	Button* dropsButton;
	Button* orbitsButton;
	Button* actionsButton;
	Button* patternsButton;
	Button* saveFileButton;

	Sprite* dropsImage;
	Sprite* orbitsImage;
	Sprite* actionsImage;
	Sprite* patternsImage;
	Sprite* saveFileImage;

	Sprite* buttonContainer;
	Sprite* saveFileContainer;

	void initVectorsAndTextFields(const char* enemyFileName);
	void saveToFile(const char* enemyFileName);

	std::vector<std::vector<std::string> > parseDrops(FILE* fp);
	std::vector<std::vector<std::string> > parseActions(FILE* fp);
	std::vector<std::vector<std::string> > parsePatterns(FILE* fp);
	std::vector<std::vector<std::string> > parseOrbits(FILE* fp);

	std::vector<std::string> parsePattern(FILE* fp);
	std::vector<std::string> parseOrbit(FILE* fp);

	void writeTextFields(FILE* fp);
	void writePatterns(FILE* fp);
	void writeActions(FILE* fp);
	void writeOrbits(FILE* fp);
	void writeDrops(FILE* fp);
	void writeAttribute(FILE* fp,
			std::vector<std::vector<std::string> > vector);

public:
	WindowStateEnemyAttributeSelect(StateArgs arguments);
	virtual ~WindowStateEnemyAttributeSelect();

	int update(double dt);
	void render(float cameraX = 0, float cameraY = 0);
	void handleUnstack(StateArgs arguments);
	StateArgs unloadArguments();
	StateArgs passArguments();
};

#endif /* WINDOWSTATEENEMYATTRIBUTESELECT_H_ */
