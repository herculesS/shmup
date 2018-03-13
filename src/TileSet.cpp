/*
 * TileSet.cpp
 *
 *  Created on: 07/05/2013
 *      Author: Vitor
 */

#include "TileSet.h"

TileSet::TileSet(std::string fileName, int tileWidth, int tileHeight) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->useSingleFile = true;
	this->tileSet = new Sprite(fileName);
	this->lines = this->tileSet->getHeight() / tileHeight;
	this->columns = this->tileSet->getWidth() / tileWidth;
}

TileSet::TileSet(int tileWidth, int tileHeight) {
	this->tileSet = NULL;
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;
	this->useSingleFile = false;
	this->lines = 0;
	this->columns = 0;
}

TileSet::~TileSet() {
	for (std::vector<Sprite*>::iterator it = vTiles.begin(); it != vTiles.end();
			it++) {
		delete *it;
	}
	delete this->tileSet;
}

void TileSet::addTile(std::string fileName) {
	if (!useSingleFile) {
		tileSet = new Sprite(fileName);
		vTiles.push_back(tileSet);
	}
}

void TileSet::render(int index, float posX, float posY) {
	if (useSingleFile) {
		int x = (index - 1) % columns;
		int y = (index - 1) / lines;
		tileSet->clip(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
		tileSet->render((int) posX, (int) posY, false);
	} else {
		vTiles[index]->render((int) posX, (int) posY, false);
	}
}

bool TileSet::usingSingleFile() {
	return useSingleFile;
}

int TileSet::getTileHeight() {
	return this->tileHeight;
}

int TileSet::getTileWidth() {
	return this->tileWidth;
}
