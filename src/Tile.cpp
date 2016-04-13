#include <iostream>
#include <gtkmm.h>

#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"

using namespace std;

Tile::Tile(Map* containerInput, int xInput, int yInput, Tile::Terrain terrainInput)
{
	container = containerInput;
	x = xInput;
	y = yInput;
	terrain = terrainInput;
	building = nullptr;
}

int Tile::getX() const
{
	return x;
}


int Tile::getY() const
{
	return y;
}

void Tile::newBuilding(Building::Type buildingInput)
{
	if(terrain == Tile::Terrain::WATER ||
		terrain == Tile::Terrain::FISH ||
		terrain == Tile::Terrain::FOREST ||
		terrain == Tile::Terrain::ROCK)
	{
		std::cout << "newBuilding : (" << x << ", " << y << ") : this tile is not buildable" << std::endl;
	}
	else if(building == nullptr)
	{
		building = new Building(this, buildingInput);
		container->invalidateTile(x, y);
		std::cout << "newBuilding : (" << x << ", " << y << ") : Building created" << std::endl;
	}

	else
	{
		std::cout << "newBuilding : (" << x << ", " << y << ") : There is alrady a building here" << std::endl;
	}
}

Building* Tile::getBuilding() const
{
	return building;
}

Tile::Terrain Tile::getTerrain() const
{
	return terrain;
}

Map* Tile::getContainer() const
{
	return container;
}

Tile* Tile::getNeighbour(Direction direction) const
{
	switch(direction)
	{
		case Direction::N :
			return container->getTile(x, y+1);
			break;

		case Direction::NE :
			return container->getTile(x+1, y-1);
			break;

		case Direction::E :
			return container->getTile(x+1, y);
			break;

		case Direction::SE :
			return container->getTile(x+1, y+1);
			break;

		case Direction::S :
			return container->getTile(x, y+1);
			break;

		case Direction::SW :
			return container->getTile(x-1, y+1);
			break;
		case Direction::W :
			return container->getTile(x-1, y);
			break;

		case Direction::NW :
			return container->getTile(x-1, y-1);
			break;
	}
};



void Tile::deleteBuilding()
{
	if(building == nullptr)
	{
		std::cout << "deleteBuilding : (" << x << ", " << y << ") : There is no building to destroy here" << std::endl;
	}
	else
	{
		delete building;
		building = nullptr;
		container->invalidateTile(x, y);
		std::cout << "deleteBuilding : (" << x << ", " << y << ") : Building destroyed" << std::endl;
	}
}

void Tile::draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	int mapHeight = container->getHeight();
	int mapWidth = container->getWidth();
	int a = x*TILE_WIDTH - y*TILE_WIDTH; //offset x
	int b = x*TILE_HEIGHT + y*TILE_HEIGHT; //offset y
	switch(terrain)
	{
		case Tile::Terrain::GRASS:
			cr->set_source_rgb(0.20,0.73,0.13);
			break;
		case Tile::Terrain::FARMABLE:
			cr->set_source_rgb(1, 0.7, 0);
			break;
		case Tile::Terrain::WATER:
			cr->set_source_rgb(0.19,0.55,0.80);
			break;
		case Tile::Terrain::FISH:
			cr->set_source_rgb(0.11,0.42,0.64);
			break;
		case Tile::Terrain::ROCK:
			cr->set_source_rgb(0.5, 0.5, 0.5);
			break;
		case Tile::Terrain::FOREST:
			cr->set_source_rgb(0.07,0.57,0.19);
			break;
	}
	cr->move_to(mapHeight*TILE_WIDTH + a, 0 + b);
	cr->line_to(mapHeight*TILE_WIDTH + TILE_WIDTH + a, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a, 2*TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH - TILE_WIDTH + a, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a, 0 + b);
	cr->fill();
}

void Tile::printBuilding() const
{
	if(building == nullptr)
	{
		std::cout << "printBuilding: (" << x << ", " << y << ") : No building here" << std::endl;
	}
	else
	{
		std::cout << "printBuilding: (" << x << ", " << y << ") : " << building << std::endl;
	}
}

