/*
 * TileSet.h
 *
 *  Created on: 07/05/2013
 *      Author: Vitor
 */

#ifndef TILESET_H_
#define TILESET_H_

#include "Sprite.h"
#include <string>
#include <vector>

class TileSet {
private:
	int tileHeight;
	int tileWidth;
	int lines;
	int columns;
	Sprite* tileSet;
	std::vector<Sprite*> vTiles;
	SDL_Rect destRect;
	bool useSingleFile;

public:
	TileSet(std::string fileName, int tileWidth, int tileHeight);
	TileSet(int tileWidth, int tileHeight);
	virtual ~TileSet();

	void addTile(std::string fileName);
	void render(int index, float posX, float posY);
	bool usingSingleFile();
	int getTileWidth();
	int getTileHeight();
};

#endif /* TILESET_H_ */
