/*
 * WindowStateEnemyAttributeSelect.cpp
 *
 *  Created on: 26/07/2013
 *      Author: vitor
 */

#include "WindowStateEnemyAttributeSelect.h"

WindowStateEnemyAttributeSelect::WindowStateEnemyAttributeSelect(
		StateArgs arguments) :
		WindowState("Atributos do inimigo") {
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	buttonContainer = new Sprite("../gfx/buttonContainer.png");
	saveFileContainer = new Sprite("../gfx/invisibleSprite.png");
	saveFileImage = new Sprite("../gfx/saveFileImage.png");
	dropsImage = new Sprite("../gfx/upgradeDropImage.png");
	orbitsImage = new Sprite("../gfx/orbitsImage.png");
	patternsImage = new Sprite("../gfx/spreadPatternImage.png");
	actionsImage = new Sprite("../gfx/moveActionImage.png");

	accessingDrops = false;
	accessingActions = false;
	accessingPatterns = false;
	accessingOrbits = false;

	patternsButton = new Button(Point(ATTRIBUTE_BASE_X, ATTRIBUTE_BASE_Y),
			buttonContainer, patternsImage);
	actionsButton = new Button(
			Point(ATTRIBUTE_BASE_X + ATTRIBUTE_OFFSET, ATTRIBUTE_BASE_Y),
			buttonContainer, actionsImage);
	orbitsButton = new Button(
			Point(ATTRIBUTE_BASE_X + 2 * ATTRIBUTE_OFFSET, ATTRIBUTE_BASE_Y),
			buttonContainer, orbitsImage);
	dropsButton = new Button(
			Point(ATTRIBUTE_BASE_X + 3 * ATTRIBUTE_OFFSET, ATTRIBUTE_BASE_Y),
			buttonContainer, dropsImage);
	saveFileButton = new Button(Point(SAVE_FILE_X, SAVE_FILE_Y),
			saveFileContainer, saveFileImage);

	enemyFileName = arguments.getArg(0);

	subTitle = new Text("../ttf/Arial-Black.ttf", enemyFileName, 12, 0, color,
			SUBTITLE_X, SUBTITLE_Y);

	initVectorsAndTextFields(enemyFileName.c_str());
}

WindowStateEnemyAttributeSelect::~WindowStateEnemyAttributeSelect() {
	delete (subTitle);
	delete (buttonContainer);
	delete (saveFileContainer);
	delete (saveFileImage);
	delete (saveFileButton);
	delete (dropsImage);
	delete (orbitsImage);
	delete (patternsImage);
	delete (actionsImage);
	delete (patternsButton);
	delete (actionsButton);
	delete (orbitsButton);
	delete (dropsButton);
	delete (lifeTextField);
	delete (spriteIndexTextField);
	delete (pointsTextField);
}

int WindowStateEnemyAttributeSelect::update(double dt) {

	nextState = WindowState::STATENOCHANGE;
	accessingDrops = false;
	accessingActions = false;
	accessingPatterns = false;
	accessingOrbits = false;

	dropsButton->update();
	actionsButton->update();
	patternsButton->update();
	orbitsButton->update();
	saveFileButton->update();

	lifeTextField->update();
	spriteIndexTextField->update();
	pointsTextField->update();

	if (saveFileButton->isClicked()) {
		saveToFile(enemyFileName.c_str());
	}
	if (dropsButton->isClicked()) {
		nextState = WindowState::STATEDROPPABLESELECT;
		accessingDrops = true;
	}
	if (actionsButton->isClicked()) {
		nextState = WindowState::STATEACTIONSELECT;
		accessingActions = true;
	}
	if (patternsButton->isClicked()) {
		nextState = WindowState::STATEPATTERNSELECT;
		accessingPatterns = true;
	}
	if (orbitsButton->isClicked()) {
		nextState = WindowState::STATEORBITSELECT;
		accessingOrbits = true;
	}

	if (returnChanges) {
		nextState = WindowState::STATEDESTROY;
		saveToFile(enemyFileName.c_str());
	}

	return nextState;
}

void WindowStateEnemyAttributeSelect::render(float cameraX, float cameraY) {
	WindowState::render(cameraX, cameraY);
	subTitle->render(cameraX, cameraY, true);

	dropsButton->render(cameraX, cameraY);
	actionsButton->render(cameraX, cameraY);
	patternsButton->render(cameraX, cameraY);
	orbitsButton->render(cameraX, cameraY);
	saveFileButton->render(cameraX, cameraY);

	lifeTextField->render(cameraX, cameraY);
	spriteIndexTextField->render(cameraX, cameraY);
	pointsTextField->render(cameraX, cameraY);
}

StateArgs WindowStateEnemyAttributeSelect::passArguments() {

	if (accessingDrops) {
		return StateArgs(dropsVector);
	}
	if (accessingActions) {
		return StateArgs(actionsVector);
	}
	if (accessingOrbits) {
		return StateArgs(orbitsVector);
	}

	return StateArgs(patternsVector);

}

StateArgs WindowStateEnemyAttributeSelect::unloadArguments() {
	return StateArgs();
}

void WindowStateEnemyAttributeSelect::handleUnstack(StateArgs arguments) {

	if (accessingDrops) {
		dropsVector = arguments.getAllArgs();
	} else if (accessingActions) {
		actionsVector = arguments.getAllArgs();
	} else if (accessingOrbits) {
		orbitsVector = arguments.getAllArgs();
	} else {
		patternsVector = arguments.getAllArgs();
	}

}

void WindowStateEnemyAttributeSelect::initVectorsAndTextFields(
		const char* enemyFileName) {

	FILE* enemyFile;
	char stringRead[50];

	enemyFile = fopen(enemyFileName, "r");
	if (enemyFile == NULL) {
		fprintf(stderr,
				"Enemy Attribute Selector: nao consegui abrir o arquivo %s.\n",
				enemyFileName);
		exit(1);
	}

	while (!feof(enemyFile)) {
		fscanf(enemyFile, "%s", stringRead);

		if (strcasecmp(stringRead, "patterns") == 0) {
			patternsVector = parsePatterns(enemyFile);
		} else if (strcasecmp(stringRead, "actions") == 0) {
			actionsVector = parseActions(enemyFile);
		} else if (strcasecmp(stringRead, "orbits") == 0) {
			orbitsVector = parseOrbits(enemyFile);
		} else if (strcasecmp(stringRead, "drops") == 0) {
			dropsVector = parseDrops(enemyFile);
		} else if (strcasecmp(stringRead, "life") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%s", stringRead);
			lifeTextField = new LabeledTextField(
					Point(TEXT_FIELD_BASE_X, TEXT_FIELD_BASE_Y), "Vida",
					std::string(stringRead));
		} else if (strcasecmp(stringRead, "sprite") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%s", stringRead);
			spriteIndexTextField = new LabeledTextField(
					Point(TEXT_FIELD_BASE_X,
							TEXT_FIELD_BASE_Y + TEXT_FIELD_OFFSET),
					"Indice do Sprite", std::string(stringRead));
		} else if (strcasecmp(stringRead, "points") == 0) {
			fscanf(enemyFile, "%s", stringRead);
			fscanf(enemyFile, "%s", stringRead);
			pointsTextField = new LabeledTextField(
					Point(TEXT_FIELD_BASE_X,
							TEXT_FIELD_BASE_Y + 2 * TEXT_FIELD_OFFSET),
					"Pontos", std::string(stringRead));
		} else {
			fprintf(stderr, "%s: palavra nao reconhecida: '%s'.\n",
					enemyFileName, stringRead);
			exit(1);
		}
	}

	fclose(enemyFile);

}

std::vector<std::vector<std::string> > WindowStateEnemyAttributeSelect::parsePatterns(
		FILE* fp) {
	std::vector<std::vector<std::string> > toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {
		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {
			if (strcasecmp(stringRead, "pattern") == 0) {
				std::vector<std::string> parseReturn = parsePattern(fp);
				parseReturn.insert(parseReturn.begin(), "pattern");
				toReturn.push_back(parseReturn);
			} else {
				fprintf(stderr,
						"parsePatterns: palavra nao reconhecida '%s', esperava 'pattern'.\n",
						stringRead);
				exit(1);
			}

			fscanf(fp, "%s", stringRead);
		}
	} else {
		fprintf(stderr, "parsePatterns: esperava 'begin', encontrou %s.\n",
				stringRead);
		exit(1);
	}

	return toReturn;

}

std::vector<std::string> WindowStateEnemyAttributeSelect::parsePattern(
		FILE* fp) {
	std::vector<std::string> toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	toReturn.push_back(std::string(stringRead));

	if (strcasecmp(stringRead, "flower") == 0) {
		for (int i = 0; i < 8; i++) {
			fscanf(fp, "%s", stringRead);
			toReturn.push_back(std::string(stringRead));
		}
	} else if (strcasecmp(stringRead, "spread") == 0) {
		for (int i = 0; i < 7; i++) {
			fscanf(fp, "%s", stringRead);
			toReturn.push_back(std::string(stringRead));
		}
	} else if (strcasecmp(stringRead, "burst") == 0) {
		for (int i = 0; i < 6; i++) {
			fscanf(fp, "%s", stringRead);
			toReturn.push_back(std::string(stringRead));
		}
	} else {
		fprintf(stderr, "Pattern nao reconhecido: %s.\n", stringRead);
		exit(1);
	}

	return toReturn;
}

std::vector<std::vector<std::string> > WindowStateEnemyAttributeSelect::parseActions(
		FILE* fp) {
	std::vector<std::vector<std::string> > toReturn;
	std::vector<std::string> parsedAction;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {

			parsedAction.clear();
			parsedAction.push_back(std::string(stringRead));

			if (strcasecmp(stringRead, "move") == 0) {
				for (int i = 0; i < 3; i++) {
					fscanf(fp, "%s", stringRead);
					parsedAction.push_back(std::string(stringRead));
				}
			} else if (strcasecmp(stringRead, "movestraight") == 0) {
				for (int i = 0; i < 2; i++) {
					fscanf(fp, "%s", stringRead);
					parsedAction.push_back(std::string(stringRead));
				}
			} else if (strcasecmp(stringRead, "shoot") == 0) {
			} else if (strcasecmp(stringRead, "wait") == 0) {
				fscanf(fp, "%s", stringRead);
				parsedAction.push_back(std::string(stringRead));
			} else if (strcasecmp(stringRead, "stopshooting") == 0) {
			} else if (strcasecmp(stringRead, "add") == 0) {
				std::vector<std::string> patternReturn = parsePattern(fp);
				parsedAction.insert(parsedAction.end(), patternReturn.begin(),
						patternReturn.end());
			} else if (strcasecmp(stringRead, "orbit") == 0) {
				std::vector<std::string> orbitReturn = parseOrbit(fp);
				parsedAction.insert(parsedAction.end(), orbitReturn.begin(),
						orbitReturn.end());
			} else if (strcasecmp(stringRead, "die") == 0) {
			} else {
				fprintf(stderr, "Action nao reconhecida: %s.\n", stringRead);
				exit(1);
			}

			fscanf(fp, "%s", stringRead);

			toReturn.push_back(parsedAction);
		}
	} else {
		fprintf(stderr, "parseActions: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

	return toReturn;

}

std::vector<std::vector<std::string> > WindowStateEnemyAttributeSelect::parseOrbits(
		FILE* fp) {
	std::vector<std::vector<std::string> > toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {

			if (strcasecmp(stringRead, "orbit") != 0) {
				fprintf(stderr,
						"Orbit parser: esperava 'orbit', encontrou '%s'.\n",
						stringRead);
				exit(1);
			}

			std::vector<std::string> parsedOrbit = parseOrbit(fp);
			parsedOrbit.insert(parsedOrbit.begin(), "orbit");

			toReturn.push_back(parsedOrbit);

			fscanf(fp, "%s", stringRead);

		}

	} else {
		fprintf(stderr, "Orbit parser: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

	return toReturn;
}

std::vector<std::string> WindowStateEnemyAttributeSelect::parseOrbit(FILE* fp) {
	std::vector<std::string> toReturn;
	char stringRead[50];

	for (int i = 0; i < 5; i++) {
		fscanf(fp, "%s", stringRead);
		toReturn.push_back(std::string(stringRead));
	}

	return toReturn;
}

std::vector<std::vector<std::string> > WindowStateEnemyAttributeSelect::parseDrops(
		FILE* fp) {

	std::vector<std::vector<std::string> > toReturn;
	char stringRead[50];

	fscanf(fp, "%s", stringRead);

	if (strcasecmp(stringRead, "begin") == 0) {

		fscanf(fp, "%s", stringRead);

		while (strcasecmp(stringRead, "end") != 0) {

			std::vector<std::string> parsedDrop;
			parsedDrop.clear();

			parsedDrop.push_back(std::string(stringRead));

			if (strcasecmp(stringRead, "spread") == 0) {
			} else if (strcasecmp(stringRead, "laser") == 0) {
			} else if (strcasecmp(stringRead, "missile") == 0) {
			} else if (strcasecmp(stringRead, "upgrade") == 0) {
				fscanf(fp, "%s", stringRead);
				parsedDrop.push_back(std::string(stringRead));
			} else if (strcasecmp(stringRead, "bomb") == 0) {
			} else {
				fprintf(stderr, "Drop parser: palavra nao esperada: %s.\n",
						stringRead);
				exit(1);
			}

			toReturn.push_back(parsedDrop);

			fscanf(fp, "%s", stringRead);

		}

	} else {
		fprintf(stderr, "Drop parser: esperava 'begin', encontrou '%s'.\n",
				stringRead);
		exit(1);
	}

	return toReturn;

}

void WindowStateEnemyAttributeSelect::saveToFile(const char* enemyFileName) {

	FILE* enemyFile;

	enemyFile = fopen(enemyFileName, "w");
	if (enemyFile == NULL) {
		fprintf(stderr,
				"Enemy Attribute Selector: Nao consegui abrir o arquivo %s.\n",
				enemyFileName);
		exit(1);
	}

	writeTextFields(enemyFile);
	writePatterns(enemyFile);
	writeActions(enemyFile);
	writeOrbits(enemyFile);
	writeDrops(enemyFile);

	fclose(enemyFile);

}

void WindowStateEnemyAttributeSelect::writeTextFields(FILE* fp) {
	fprintf(fp, "life = %s\n", lifeTextField->getTextFieldString().c_str());
	fprintf(fp, "sprite = %s\n",
			spriteIndexTextField->getTextFieldString().c_str());
	fprintf(fp, "points = %s\n", pointsTextField->getTextFieldString().c_str());
	fprintf(fp, "\n");
}

void WindowStateEnemyAttributeSelect::writePatterns(FILE* fp) {
	fprintf(fp, "patterns\n");
	writeAttribute(fp, patternsVector);
	fprintf(fp, "\n");
	fprintf(fp, "\n");
}

void WindowStateEnemyAttributeSelect::writeActions(FILE* fp) {
	fprintf(fp, "actions\n");
	writeAttribute(fp, actionsVector);
	fprintf(fp, "\n");
	fprintf(fp, "\n");
}

void WindowStateEnemyAttributeSelect::writeOrbits(FILE* fp) {
	fprintf(fp, "orbits\n");
	writeAttribute(fp, orbitsVector);
	fprintf(fp, "\n");
	fprintf(fp, "\n");
}

void WindowStateEnemyAttributeSelect::writeDrops(FILE* fp) {
	fprintf(fp, "drops\n");
	writeAttribute(fp, dropsVector);
}

void WindowStateEnemyAttributeSelect::writeAttribute(FILE* fp,
		std::vector<std::vector<std::string> > vector) {
	fprintf(fp, "begin\n");
	for (unsigned int i = 0; i < vector.size(); i++) {
		fprintf(fp, "\t");
		for (unsigned int j = 0; j < vector[i].size(); j++) {
			fprintf(fp, "%s ", vector[i][j].c_str());
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "end");
}
