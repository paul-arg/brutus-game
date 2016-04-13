#include <iostream>
#include <string>
#include <cmath>

#include "basicFunctions.hpp"
#include "Tile.hpp"

using namespace std;

int screenToIsoX(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY)
{
	return floor((-offsetX*tileHeight + xScreen*tileHeight - offsetY*tileWidth + tileWidth*yScreen) / (2*tileWidth*tileHeight));
}

int screenToIsoY(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY)
{
	return floor((offsetX*tileHeight - xScreen*tileHeight - offsetY*tileWidth + tileWidth*yScreen) / (2*tileWidth*tileHeight));
}

//upper corner of the tile
int isoToScreenX(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY)
{
	return xIso*tileWidth - yIso*tileWidth + offsetX;
}

int isoToScreenY(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY)
{
	return xIso*tileHeight + yIso*tileHeight + offsetY;
}

std::string getTerrainString(Tile::Terrain terrain)
{
	switch(terrain)
	{
		case Tile::Terrain::GRASS:
			return "grass";
			break;
			
		case Tile::Terrain::FARMABLE:
			return "farmable";
			break;
			
		case Tile::Terrain::WATER:
			return "water";
			break;
			
		case Tile::Terrain::FISH:
			return "fish";
			break;
			
		case Tile::Terrain::FOREST:
			return "forest";
			break;
			
		case Tile::Terrain::ROCK:
			return "rock";
			break;
	}
}

