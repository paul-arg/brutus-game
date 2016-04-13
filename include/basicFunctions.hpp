#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>

#include "Tile.hpp"

using namespace std;

int screenToIsoX(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY);
int screenToIsoY(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY);
int isoToScreenX(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY);
int isoToScreenY(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY);

std::string getTerrainString(Tile::Terrain terrain);

#endif
