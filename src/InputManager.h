/*
 * InputManager.h
 *
 *  Created on: 14/05/2013
 *      Author: vitor
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "SDL/SDL.h"

#define N_KEYS 323
#define N_MOUSE_BUTTONS 7

class InputManager {
private:
	static InputManager* instance;

	Uint8 mouse;
	Uint8* teclado;
	Uint8 keyDown[N_KEYS], keyUp[N_KEYS];
	Uint8 mouseButtonsDown[N_MOUSE_BUTTONS], mouseButtonsUp[N_MOUSE_BUTTONS];
	int mouseX, mouseY;
	bool quitGame;

	void initMouse();
	void initKeyboard();

	InputManager();

public:
	virtual ~InputManager();

	static InputManager* getInstance() {
		if (!instance) {
			instance = new InputManager();
		}
		return instance;
	}

	void update();
	bool isKeyDown(int key);
	int getDownKey(int intervalStart, int intervalEnd);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isMouseDown(int button);
	bool isMouseUp(int button);
	bool isMousePressed(int button);
	int mousePosX();
	int mousePosY();
	bool isMouseInside(SDL_Rect* rect);
	bool QuitGame();

};

#endif /* INPUTMANAGER_H_ */
