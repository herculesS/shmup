/*
 * WindowState.h
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#ifndef WINDOWSTATE_H_
#define WINDOWSTATE_H_

#include "StateArgs.h"
#include "Text.h"
#include <string>
#include "Button.h"

#define TITLE_POSITION_X 400
#define TITLE_POSITION_Y 30

#define TEXT_FIELD_BASE_X 400
#define TEXT_FIELD_BASE_Y 130
#define TEXT_FIELD_OFFSET 60

class WindowState {
private:
	Text* title;

protected:
	int nextState;
	bool returnChanges;

public:
	WindowState(std::string title);
	virtual ~WindowState();

	virtual StateArgs unloadArguments() = 0;
	virtual StateArgs passArguments() = 0;
	virtual int update(double dt) = 0;
	virtual void render(float cameraX = 0, float cameraY = 0);
	virtual void handleUnstack(StateArgs arguments) = 0;
	virtual void returnWithChanges();

	enum {
		STATENOCHANGE = 100,
		STATEDESTROY,
		STATEQUITEDITOR,
		STATEQUITGAME,
		STATEPATTERNFLOWER,
		STATEPATTERNBURST,
		STATEPATTERNSPREAD,
		STATEACTIONMOVE,
		STATEACTIONMOVESTRAIGHT,
		STATEACTIONWAIT,
		STATEACTIONADDPATTERN,
		STATEPATTERNSELECT,
		STATEPATTERNCREATESELECT,
		STATEACTIONSELECT,
		STATEACTIONCREATESELECT,
		STATEDROPPABLEUPGRADE,
		STATEDROPPABLESELECT,
		STATEDROPPABLECREATESELECT,
		STATEENEMYATTRIBUTESELECT,
		STATEORBIT,
		STATEORBITSELECT,
		STATEWAVEENEMY,
		STATEWAVEENEMYSELECT
	};
};

#endif /* WINDOWSTATE_H_ */
