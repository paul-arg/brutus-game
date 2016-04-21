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

Tile::~Tile()
{
    if (building != nullptr)
	{
		destroyBuilding();
	}
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
	if(!isBuildable() || !container->hasRoom(x, y, dictBuildingSize(buildingInput)))
	{
		std::cout << "newBuilding : (" << x << ", " << y << ") : this tile is not buildable" << std::endl;
	}
	else
	{
		building = new Building(this, buildingInput);
		container->invalidateZone(x, y, building->getSize());
		std::cout << "newBuilding : (" << x << ", " << y << ") : " << dictBuildingString(buildingInput) << " created" << std::endl;
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



void Tile::destroyBuilding()
{
	if(building == nullptr)
	{
		std::cout << "destroyBuilding : (" << x << ", " << y << ") : There is no building to destroy here" << std::endl;
	}
	else
	{
		const int xSupport = building->getSupport()->getX();
		const int ySupport = building->getSupport()->getY();
		const int size = building->getSize();
		const std::string type = dictBuildingString(building->getType());
		delete building;
		container->invalidateZone(xSupport, ySupport, size);
		std::cout << "destroyBuilding : (" << x << ", " << y << ") : " << type << " destroyed" << std::endl;
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
	cr->move_to(mapHeight*TILE_WIDTH + a             , 0 + b);
	cr->line_to(mapHeight*TILE_WIDTH + TILE_WIDTH + a, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a             , 2*TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH - TILE_WIDTH + a, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a             , 0 + b);
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

void Tile::setBuilding(Building* buildingInput)
{
	building = buildingInput;
}

bool Tile::isBuildable() const
{
	switch(terrain)
	{
		
		case Tile::Terrain::GRASS :
			return true;
			break;
		case Tile::Terrain::FARMABLE :
			return true;
			break;
		case Tile::Terrain::WATER :
			return false;
			break;
		case Tile::Terrain::FISH :
			return false;
			break;
		case Tile::Terrain::ROCK :
			return false;
			break;
		case Tile::Terrain::FOREST :
			return false;
			break;
	}
}

std::string dictTerrainString(Tile::Terrain terrain)
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

