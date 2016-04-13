#include <iostream>
#include <set>
#include <gtkmm.h>

#include "Map.hpp"
#include "Tile.hpp"
#include "basicFunctions.hpp"

using namespace std;

Map::Map(int mapHeightInput, int mapWidthInput)
: mapHeight(mapHeightInput), mapWidth(mapWidthInput)
{
	mapData = new Tile**[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		mapData[i] = new Tile*[mapHeight];
	}

	// Null out the pointers contained in the array:
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			mapData[i][j] = nullptr;
		}
	}
}

void Map::drawGrid(const Cairo::RefPtr<Cairo::Context>& cr)
{
	int i;
	cr->set_line_width(0.25);
	Gdk::Cairo::set_source_color( cr, Gdk::Color( "black" ) );
	for(i=0; i <= mapWidth; i++)
	{
		int iTileWidth = i*TILE_WIDTH;
		int iTileHeight = i*TILE_HEIGHT;
		cr->move_to(0 + iTileWidth, mapHeight*TILE_HEIGHT + iTileHeight);
		cr->line_to(mapHeight*TILE_WIDTH + iTileWidth, iTileHeight);
		cr->stroke();
	}
	
	for(i=0; i <= mapHeight; i++)
	{
		int iTileWidth = i*TILE_WIDTH;
		int iTileHeight = i*TILE_HEIGHT;
		cr->move_to(0 + iTileWidth, mapHeight*TILE_HEIGHT - iTileHeight);
		cr->line_to(mapWidth*TILE_WIDTH + iTileWidth, mapHeight*TILE_HEIGHT + mapWidth*TILE_HEIGHT - iTileHeight);
		cr->stroke();
	}
}

int Map::getHeight() const
{
	return mapHeight;
}

int Map::getWidth() const
{
	return mapWidth;
}

bool Map::isThereRoom(int x, int y, int size) const
//check if there is no building in the square of size "size" starting from support
//support tile is the bottom tile of the square
{
	switch(size)
	{
		case 1:
			return getTile(x, y)->getBuilding() == nullptr;
			break;
			
		case 2:
			return( isThereRoom(x, y, 1) &&
				isThereRoom(x - 1, y, 1) &&
				isThereRoom(x, y - 1 , 1) &&
				isThereRoom(x - 1, y - 1, 1) );
			break;
			
		case 3:
			return( isThereRoom(x, y, 2) &&
				isThereRoom(x - 2, y, 1) &&
				isThereRoom(x - 2, y - 1, 1) &&
				isThereRoom(x - 2, y - 2, 1) &&
				isThereRoom(x - 1 , y - 2, 1) &&
				isThereRoom(x, y - 2, 1) );
			break;
			
		case 4:
			return( isThereRoom(x, y, 2) &&
				isThereRoom(x - 2, y, 2) &&
				isThereRoom(x, y - 2, 2) &&
				isThereRoom(x - 2, y - 2, 2) );
			break;
	}
}

void Map::newTile(int x, int y, Tile::Terrain terrain)
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		std::cout << "newTile : (" << x << ", " << y << ") : You are beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] != nullptr)
	{
		std::cout << "newTile : (" << x << ", " << y << ") : There is alrady a " << getTerrainString(mapData[x][y]->getTerrain()) << " tile here" << std::endl;
	}
	else
	{
		invalidateTile(x, y);
		mapData[x][y] = new Tile(this, x, y, terrain);
		std::cout << "newTile : (" << x << ", " << y << ") : " << getTerrainString(mapData[x][y]->getTerrain()) << " tile created" << std::endl;
	}
}

void Map::fillWith(Tile::Terrain paint)
{
	int i;
	int j;
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if(mapData[i][j] == nullptr)
			{
				newTile(i, j, paint);
			}
		}
	}
}

void Map::invalidateTile(int x, int y)
{
	auto win = container->get_window();
		if (win)
		{
			Gdk::Rectangle r(
				isoToScreenX(x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight*TILE_WIDTH, 0) - TILE_WIDTH,
				isoToScreenY(x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight*TILE_WIDTH, 0),
				2*TILE_WIDTH,
				2*TILE_HEIGHT
				);
			win->invalidate_rect(r, false);
		}
}

Tile* Map::getTile(int x, int y) const
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		return nullptr;
	}
	else
	{
		return mapData[x][y];
	}
}

GameView* Map::getContainer() const
{
	return container;
}

void Map::setContainer(GameView* containerInput)
{
	container = containerInput;
}

void Map::printTile(int x, int y) const
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		std::cout << "printTile : (" << x << ", " << y << ") : You are beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] == nullptr)
	{
		std::cout << "printTile : (" << x << ", " << y << ") : No tile here" << std::endl;
	}
	else
	{
		std::cout << "printTile : (" << x << ", " << y << ") : " << mapData[x][y] << " : " << getTerrainString(mapData[x][y]->getTerrain()) << " tile"<<std::endl;
	}
}

void Map::deleteTile(int x, int y)
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		std::cout << "deleteTile : (" << x << ", " << y << ") : You are beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] == nullptr)
	{
		std::cout << "deleteTile : (" << x << ", " << y << ") : There is no tile here" << std::endl;
	}
	else
	{
		std::string terrainString = getTerrainString(mapData[x][y]->getTerrain());
		delete mapData[x][y];
		mapData[x][y] = nullptr;
		invalidateTile(x, y);
		std::cout << "deleteTile : (" << x << ", " << y << ") : " << terrainString << " tile deleted" << std::endl;
	}
}



