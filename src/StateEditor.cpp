/*
 * StateEditor.cpp
 *
 *  Created on: 22/07/2013
 *      Author: vitor
 */

#include "StateEditor.h"

StateEditor::StateEditor() {
}

StateEditor::~StateEditor() {
	unload();
}

void StateEditor::load(StateArgs arguments) {
	background = new Sprite("../gfx/background.jpg");

	this->exitEditorSpriteContainer = new Sprite("../gfx/invisibleSprite.png");
	this->exitEditorSprite = new Sprite("../gfx/cancelButtonImage.png");
	this->goBackButtonSprite = new Sprite("../gfx/leftArrow.png");
	this->confirmButtonSprite = new Sprite("../gfx/confirmImage.png");
	this->exitEditorButton = new Button(
			Point(EXIT_EDITOR_BUTTON_X, EXIT_EDITOR_BUTTON_Y), exitEditorSprite,
			exitEditorSpriteContainer);
	this->goBackButton = new Button(Point(GO_BACK_BUTTON_X, GO_BACK_BUTTON_Y),
			goBackButtonSprite, exitEditorSpriteContainer);
	this->confirmButton = new Button(Point(CONFIRM_BUTTON_X, CONFIRM_BUTTON_Y),
			confirmButtonSprite, exitEditorSpriteContainer);
	this->backgroundMusic = new Music("../sfx/TheSims-TheSimpleLife.mp3");
	backgroundMusic->play(-1);

	quitGame = false;
	quitEditor = false;
	goBack = false;
	confirmChanges = false;

	std::vector<std::string> args;

	args.push_back("../stages/wave09script.txt");
	windowStateStack.push(new WindowStateWaveEnemySelect(StateArgs(args)));
}

void StateEditor::killTopState() {
	delete (windowStateStack.top());
	windowStateStack.pop();
}

StateArgs StateEditor::unload() {
	delete (background);
	delete (exitEditorSprite);
	delete (exitEditorSpriteContainer);
	delete (exitEditorButton);
	delete (goBackButton);
	delete (goBackButtonSprite);
	delete (confirmButton);
	delete (confirmButtonSprite);
	backgroundMusic->stop();
	delete (backgroundMusic);

	while (!windowStateStack.empty()) {
		killTopState();
	}

	return StateArgs();
}

void StateEditor::input() {
	if (InputManager::getInstance()->QuitGame()) {
		quitGame = true;
	}
	if (exitEditorButton->isClicked()) {
		quitEditor = true;
	}
	if (goBackButton->isClicked()) {
		goBack = true;
	}
	if (confirmButton->isClicked()) {
		confirmChanges = true;
	}
}

int StateEditor::update(double dt) {

	StateArgs arguments;

	switch (windowStateStack.top()->update(dt)) {
	case WindowState::STATENOCHANGE:
		break;
	case WindowState::STATEDESTROY:
		arguments = windowStateStack.top()->unloadArguments();
		killTopState();
		if (!windowStateStack.empty()) {
			windowStateStack.top()->handleUnstack(arguments);
		}
		break;
	case WindowState::STATEPATTERNBURST:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStatePatternBurst(arguments));
		break;
	case WindowState::STATEPATTERNSPREAD:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStatePatternSpread(arguments));
		break;
	case WindowState::STATEPATTERNFLOWER:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStatePatternFlower(arguments));
		break;
	case WindowState::STATEACTIONMOVE:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionMove(arguments));
		break;
	case WindowState::STATEACTIONMOVESTRAIGHT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionMoveStraight(arguments));
		break;
	case WindowState::STATEACTIONWAIT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionWait(arguments));
		break;
	case WindowState::STATEACTIONADDPATTERN:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionAddPattern(arguments));
		break;
	case WindowState::STATEPATTERNSELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStatePatternSelect(arguments));
		break;
	case WindowState::STATEPATTERNCREATESELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStatePatternCreateSelect(arguments));
		break;
	case WindowState::STATEACTIONSELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionSelect(arguments));
		break;
	case WindowState::STATEACTIONCREATESELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateActionCreateSelect(arguments));
		break;
	case WindowState::STATEDROPPABLEUPGRADE:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateDroppableUpgrade(arguments));
		break;
	case WindowState::STATEDROPPABLESELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateDroppableSelect(arguments));
		break;
	case WindowState::STATEDROPPABLECREATESELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateDroppableCreateSelect(arguments));
		break;
	case WindowState::STATEENEMYATTRIBUTESELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateEnemyAttributeSelect(arguments));
		break;
	case WindowState::STATEORBIT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateOrbit(arguments));
		break;
	case WindowState::STATEORBITSELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateOrbitSelect(arguments));
		break;
	case WindowState::STATEWAVEENEMY:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateWaveEnemy(arguments));
		break;
	case WindowState::STATEWAVEENEMYSELECT:
		arguments = windowStateStack.top()->passArguments();
		windowStateStack.push(new WindowStateWaveEnemySelect(arguments));
		break;
	}

	exitEditorButton->update();
	goBackButton->update();
	confirmButton->update();

	nextState = SDLBase::STATENOCHANGE;

	if (goBack) {
		goBack = false;
		killTopState();
	}
	if (confirmChanges) {
		confirmChanges = false;
		windowStateStack.top()->returnWithChanges();
	}
	if (quitGame) {
		nextState = SDLBase::STATEQUIT;
	}
	if (quitEditor || windowStateStack.empty()) {
		nextState = SDLBase::STATEDESTROY;
	}

	return nextState;
}

void StateEditor::render() {
	background->render(0, 0, false);
	exitEditorButton->render();
	goBackButton->render();
	confirmButton->render();
	windowStateStack.top()->render();
}
