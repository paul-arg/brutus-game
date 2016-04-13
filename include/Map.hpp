#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <set>
#include <gtkmm.h>

#include "GameView.hpp"
#include "Tile.hpp"
#include "Building.hpp"

#define TILE_WIDTH 32
#define TILE_HEIGHT 16
#define OFFSET_X 192
#define OFFSET_Y 0

using namespace std;

class Map
{
	public:
		Map(int mapHeightInput, int mapWidthInput);

		int getHeight() const;
		int getWidth() const;
		Tile* getTile(int x, int y) const;
		void printTile(int x, int y) const;
		bool isThereRoom(int x, int y, int size) const;
		std::set<Tile*> getTileSet() const;
		GameView* getContainer() const;

		void newTile(int x, int y, Tile::Terrain terrain);
		void deleteTile(int x, int y);
		void drawGrid(const Cairo::RefPtr<Cairo::Context>& cr);
		void setContainer(GameView*);
		void invalidateTile(int x, int y);
		void fillWith(Tile::Terrain paint);
	
	private:
		GameView* container;
		int mapHeight;
		int mapWidth;
		Tile*** mapData;
};

#endif
