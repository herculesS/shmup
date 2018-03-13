/*
 * TileMap.h
 *
 *  Created on: 09/05/2013
 *      Author: Vitor
 */

#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"
#include <vector>

class TileMap {
private:
	std::vector<std::vector<std::vector<int> > > tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapLayers;

	void initializeValues();
	void resizeMap(int mapHeight, int mapWidth, int mapLayers);

public:
	TileMap(int mapWidth, int mapHeight, int mapLayers, int tileSize,
			TileSet* tileSet);
	TileMap(std::string mapFile, TileSet* tileSet);
	virtual ~TileMap();

	void load(std::string mapFile);
	void setTileSet(TileSet* newTileSet);
	int& at(int x, int y);
	void render(float cameraX, float cameraY);

	int getMapHeight() const {
		return mapHeight;
	}

	int getMapLayers() const {
		return mapLayers;
	}

	int getMapWidth() const {
		return mapWidth;
	}
};

#endif /* TILEMAP_H_ */
