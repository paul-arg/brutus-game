#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <gtkmm.h>

#include "Building.hpp"

using namespace std;

class Map;

enum class Direction {N, NE, E, SE, S, SW, W, NW};

class Tile
{
	public:
		enum Terrain {GRASS, FARMABLE, WATER, FISH, ROCK, FOREST};

		Tile(Map* container, int x, int y, Tile::Terrain terrain);
		~Tile();

		int getX() const;
		int getY() const;
		Building* getBuilding() const;
		Tile::Terrain getTerrain() const;
		Tile* getNeighbour(Direction direction) const;
		void printBuilding() const;
		Map* getContainer() const;
		bool isBuildable() const;

		void newBuilding(Building::Type buildingInput);
		void destroyBuilding();
		void setBuilding(Building* buildingInput);
		void draw(const Cairo::RefPtr<Cairo::Context>& cr);
	
	private:
		Map *container;
		int x;
		int y;
		Tile::Terrain terrain;
		Building* building;
};

std::string dictTerrainString(Tile::Terrain terrain);

#endif
