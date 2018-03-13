/*
 * WindowStateWaveEnemySelect.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "WindowStateWaveEnemySelect.h"

WindowStateWaveEnemySelect::WindowStateWaveEnemySelect(StateArgs arguments) :
		WindowState("Selecione o inimigo") {

	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	this->waveFileName = arguments.getArg(0);
	this->subTitle = new Text("../ttf/Arial-Black.ttf", waveFileName, 12, 0,
			color, SUBTITLE_POS_X, SUBTITLE_POS_Y);

	waveEnemyImage = new Sprite("../gfx/enemyImage.png");
	waveEnemyContainer = new Sprite("../gfx/buttonContainer.png");

	initVector(waveFileName.c_str());

	for (unsigned int i = 0; i < waveEnemyVector.size(); i++) {
		waveEnemyButtonVector.push_back(
				new Button(
						Point(
								ENEMY_BUTTONS_X
										+ ((i % NUM_ENEMIES_LINE)
												* ENEMY_BUTTONS_OFFSET),
								ENEMY_BUTTONS_Y
										+ ((i / NUM_ENEMIES_LINE)
												* ENEMY_BUTTONS_OFFSET)),
						waveEnemyContainer, waveEnemyImage));
	}

	clickedButtonIndex = -1;
}

WindowStateWaveEnemySelect::~WindowStateWaveEnemySelect() {
	delete (waveEnemyImage);
	delete (waveEnemyContainer);
	delete (subTitle);

	for (std::vector<Button*>::iterator it = waveEnemyButtonVector.begin();
			it != waveEnemyButtonVector.end(); ++it) {
		delete (*it);
		it = waveEnemyButtonVector.erase(it);
		it--;
	}
}

int WindowStateWaveEnemySelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;

	for (unsigned int i = 0; i < waveEnemyButtonVector.size(); i++) {
		waveEnemyButtonVector[i]->update();
		if (waveEnemyButtonVector[i]->isClicked()) {
			nextState = WindowState::STATEWAVEENEMY;
			clickedButtonIndex = i;
		}
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateWaveEnemySelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	subTitle->render(cameraX, cameraY, true);

	for (std::vector<Button*>::iterator it = waveEnemyButtonVector.begin();
		it != waveEnemyButtonVector.end(); ++it) {
		(*it)->render(cameraX, cameraY);
	}
}

StateArgs WindowStateWaveEnemySelect::passArguments() {
	return StateArgs(waveEnemyVector[clickedButtonIndex]);
}

StateArgs WindowStateWaveEnemySelect::unloadArguments() {
	return StateArgs();
}

void WindowStateWaveEnemySelect::handleUnstack(StateArgs arguments) {
	waveEnemyVector[clickedButtonIndex] = arguments.getLineArgs(0);
}

void WindowStateWaveEnemySelect::initVector(const char* waveFileName) {

	std::vector<std::string> waveLine;
	FILE* fp;
	char stringRead[50];

	fp = fopen(waveFileName, "r");
	if (fp == NULL) {
		fprintf(stderr,
				"Wave Enemy Selector: Nao consegui abrir o arquivo %s.\n",
				waveFileName);
		exit(1);
	}

	fscanf(fp, "%s", stringRead); // wave
	fscanf(fp, "%s", stringRead); // begin
	fscanf(fp, "%s", stringRead);
	while (strcasecmp(stringRead, "end") != 0) {
		waveLine.clear();

		waveLine.push_back(std::string(stringRead));
		for (int i = 0; i < 3; i++) {
			fscanf(fp, "%s", stringRead);
			waveLine.push_back(std::string(stringRead));
		}

		waveEnemyVector.push_back(waveLine);

		fscanf(fp, "%s", stringRead);
	}

	fclose(fp);

}
