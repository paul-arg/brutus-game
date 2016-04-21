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
		bool hasRoom(int x, int y, int size) const;
		GameView* getContainer() const;

		void newTile(int x, int y, Tile::Terrain terrain);
		void newTileArea(int x1, int y1, int x2, int y2, Tile::Terrain terrain);
		void deleteTile(int x, int y);
		void deleteTileArea(int x1, int y1, int x2, int y2);
		void buildArea(int x1, int y1, int x2, int y2, Building::Type type);
		void destroyArea(int x1, int y1, int x2, int y2); 
		void drawGrid(const Cairo::RefPtr<Cairo::Context>& cr);
		void setContainer(GameView*);
		void invalidateZone(int x, int y, int size);
		void fillWith(Tile::Terrain paint);
	
	private:
		GameView* container;
		int mapHeight;
		int mapWidth;
		Tile*** mapData;
};

std::string dictEditModeString(int editMode);

#endif
