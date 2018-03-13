/*
 * WindowStateOrbit.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "WindowStateOrbit.h"

WindowStateOrbit::WindowStateOrbit(StateArgs arguments) :
		WindowState("Orbita") {
	initialAngleTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Angulo inicial",
			arguments.getArg(1));
	speedTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
			"Velocidade angular", arguments.getArg(2));
	radiusTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 2 * TEXT_FIELD_OFFSET),
			"Distancia do centro", arguments.getArg(3));
	clockwiseCheckbox = new LabeledCheckbox(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 3 * TEXT_FIELD_OFFSET),
			"Sentido horario",
			strcasecmp(arguments.getArg(4).c_str(), "clk") == 0);
	enemyFileNameTextField = new LabeledTextField(
			Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y + 4 * TEXT_FIELD_OFFSET),
			"Arquivo da orbita", arguments.getArg(5));

	orbitButtonImage = new Sprite("../gfx/orbitsImage.png");
	buttonContainer = new Sprite("../gfx/buttonContainer.png");
	orbitButton = new Button(Point(ORBIT_BUTTON_X, ORBIT_BUTTON_Y),
			buttonContainer, orbitButtonImage);

}

WindowStateOrbit::~WindowStateOrbit() {
	delete (initialAngleTextField);
	delete (speedTextField);
	delete (radiusTextField);
	delete (clockwiseCheckbox);
	delete (enemyFileNameTextField);
	delete (orbitButtonImage);
	delete (buttonContainer);
	delete (orbitButton);
}

int WindowStateOrbit::update(double dt) {

	nextState = WindowState::STATENOCHANGE;

	initialAngleTextField->update();
	speedTextField->update();
	radiusTextField->update();
	clockwiseCheckbox->update();
	enemyFileNameTextField->update();

	orbitButton->update();
	if (orbitButton->isClicked()) {
		nextState = WindowState::STATEENEMYATTRIBUTESELECT;
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
	}

	return nextState;
}

void WindowStateOrbit::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);

	initialAngleTextField->render(cameraX, cameraY);
	speedTextField->render(cameraX, cameraY);
	radiusTextField->render(cameraX, cameraY);
	clockwiseCheckbox->render(cameraX, cameraY);
	enemyFileNameTextField->render(cameraX, cameraY);
	orbitButton->render(cameraX, cameraY);
}

StateArgs WindowStateOrbit::unloadArguments() {
	std::vector<std::string> toReturn;

	toReturn.push_back("orbit");
	toReturn.push_back(initialAngleTextField->getTextFieldString());
	toReturn.push_back(speedTextField->getTextFieldString());
	toReturn.push_back(radiusTextField->getTextFieldString());
	toReturn.push_back(clockwiseCheckbox->isSelected() ? "clk" : "aclk");
	toReturn.push_back(enemyFileNameTextField->getTextFieldString());

	return toReturn;
}

StateArgs WindowStateOrbit::passArguments() {
	std::vector<std::string> argumentsToPass;

	argumentsToPass.push_back(enemyFileNameTextField->getTextFieldString());

	return argumentsToPass;
}

void WindowStateOrbit::handleUnstack(StateArgs arguments) {
	//Nada.
}
