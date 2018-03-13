/*
 * TileMap.cpp
 *
 *  Created on: 09/05/2013
 *      Author: Vitor
 */

#include "TileMap.h"

TileMap::TileMap(int mapWidth, int mapHeight, int mapLayers, int tileSize,
		TileSet* tileSet) {
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->mapLayers = mapLayers;
	this->tileSet = tileSet;

	resizeMap(mapHeight, mapWidth, mapLayers);
	initializeValues();

}

TileMap::TileMap(std::string mapFile, TileSet* tileSet) {
	this->mapHeight = 0;
	this->mapWidth = 0;
	this->mapLayers = 0;
	this->tileSet = tileSet;
	load(mapFile);
}

TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}

void TileMap::resizeMap(int mapHeight, int mapWidth, int mapLayers) {

	unsigned int i, j;

	tileMatrix.resize(mapHeight);
	for (i = 0; i < tileMatrix.size(); i++) {
		tileMatrix[i].resize(mapWidth);
		for (j = 0; j < tileMatrix[i].size(); j++) {
			tileMatrix[i][j].resize(mapLayers);
		}
	}
}

void TileMap::initializeValues() {
	int i, j, k;

	for (i = 0; i < mapHeight; i++) {
		for (j = 0; j < mapWidth; j++) {
			for (k = 0; k < mapLayers; k++) {
				tileMatrix[i][j][k] = -1;
			}
		}
	}
}

void TileMap::load(std::string mapFile) {

	FILE* fp;
	int i, j, k;

	fp = fopen(mapFile.c_str(), "r");

	if (fscanf(fp, "%d,%d,%d,", &this->mapHeight, &this->mapWidth,
			&this->mapLayers) <= 0) {
		fprintf(stderr,
				"Erro na leitura das dimensões do TileMap\nValores lidos: %d %d %d.",
				this->mapHeight, this->mapWidth, this->mapLayers);
	}

	resizeMap(this->mapHeight, this->mapWidth, this->mapLayers);

	for (k = 0; k < this->mapLayers; k++) {
		for (i = 0; i < this->mapHeight; i++) {
			for (j = 0; j < this->mapWidth; j++) {
				if (fscanf(fp, "%d,", &this->tileMatrix[i][j][k]) <= 0) {
					fprintf(stderr,
							"Erro na leitura do valor do tile na posicao: %d %d %d\nValor lido: %d",
							k, i, j, tileMatrix[i][j][k]);
					exit(1);
				}
			}
		}
	}

	fclose(fp);

}

void TileMap::setTileSet(TileSet* newTileSet) {
	this->tileSet = newTileSet;
}

int& TileMap::at(int x, int y) {
	return tileMatrix[y][x][0];
}

void TileMap::render(float cameraX, float cameraY) {
	if (tileSet == NULL) {
		fprintf(stderr, "Tentando renderizar tileMap com tileSet NULL\n");
		exit(1);
	} else {
		int i, j, k;
		float fatorParallax = 0.2;

		for (k = 0; k < mapLayers; k++) {
			fatorParallax += 0.3;
			for (i = 0; i < mapHeight; i++) {
				for (j = 0; j < mapWidth; j++) {
					if (tileMatrix[i][j][k] >= 0) {
						tileSet->render(tileMatrix[i][j][k],
								(j * tileSet->getTileWidth())
										- (cameraX * fatorParallax),
								(i * tileSet->getTileHeight())
										- (cameraY * fatorParallax));
					}
				}
			}
		}
	}
}
