#include <iostream>
#include <cmath>

#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"

Building::Building(Tile* supportInput, Building::Type typeInput)
{
	support = supportInput;
	type = typeInput;
	size = dictBuildingSize(typeInput);
	polyBuildable = dictPolyBuildable(typeInput);
	int x = support->getX();
	int y = support->getY();
	int i;
	int j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			support->getContainer()->getTile(x - i, y - j)->setBuilding(this);
		}
	}
}

Building::~Building()
{
	int x = support->getX();
	int y = support->getY();
	int i;
	int j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			support->getContainer()->getTile(x - i, y - j)->setBuilding(nullptr);
		}
	}
}

int Building::getSize() const
{
	return size;
}

Tile* Building::getSupport() const
{
	return support;
}

Building::Type Building::getType()
{
	return type;
}

bool Building::isPolyBuildable()
{
	return polyBuildable;
}

void Building::draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	int t = 5;
	int u = floor((t * TILE_WIDTH) / TILE_HEIGHT);
	int mapHeight = support->getContainer()->getHeight();
	int mapWidth = support->getContainer()->getWidth();
	int a = support->getX()*TILE_WIDTH - support->getY()*TILE_WIDTH; //offset x
	int b = support->getX()*TILE_HEIGHT + support->getY()*TILE_HEIGHT; //offset y
	
	if (type == Building::Type::ROAD)
	{
		cr->set_source_rgb(1, 0, 0);
	}
	else
	{
		cr->set_source_rgb(0.6, 0.6, 0.6);
	}
	cr->move_to(mapHeight*TILE_WIDTH + a                      , 2*TILE_HEIGHT + b - t);
	cr->line_to(mapHeight*TILE_WIDTH + a + size*TILE_WIDTH - u, 2*TILE_HEIGHT + b - size*TILE_HEIGHT);
	cr->line_to(mapHeight*TILE_WIDTH + a                      , 2*TILE_HEIGHT + b - 2*size*TILE_HEIGHT + t);
	cr->line_to(mapHeight*TILE_WIDTH + a - size*TILE_WIDTH + u, 2*TILE_HEIGHT + b - size*TILE_HEIGHT);
	cr->line_to(mapHeight*TILE_WIDTH + a                      , 2*TILE_HEIGHT + b - t);
	cr->fill();
}

int dictBuildingSize(Building::Type type)
{
	switch (type)
	{
		case Building::Type::ROAD :
			return 1;
			break;
		case Building::Type::HOUSE :
			return 1;
			break;
		case Building::Type::FOUNTAIN :
			return 1;
			break;
		case Building::Type::MARKET :
			return 2;
			break;
		case Building::Type::FARM :
			return 3;
			break;
	}
}

bool dictPolyBuildable(Building::Type type)
{
	switch (type)
	{
		case Building::Type::ROAD :
			return true;
			break;
		case Building::Type::HOUSE :
			return true;
			break;
		case Building::Type::FOUNTAIN :
			return false;
			break;
		case Building::Type::MARKET :
			return false;
			break;
		case Building::Type::FARM :
			return false;
			break;
	}
}

std::string dictBuildingString(Building::Type type)
{
	switch (type)
	{
		case Building::Type::ROAD :
			return "road";
			break;
		case Building::Type::HOUSE :
			return "house";
			break;
		case Building::Type::FOUNTAIN :
			return "fountain";
			break;
		case Building::Type::MARKET :
			return "market";
			break;
		case Building::Type::FARM :
			return "farm";
			break;
	}
}
