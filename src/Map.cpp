#include <iostream>
#include <cmath>
#include <gtkmm.h>

#include "Map.hpp"
#include "Tile.hpp"


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

bool Map::hasRoom(int x, int y, int size) const
//check if there is no building in the square of size "size" starting from support
//support tile is the bottom tile of the square
{
	switch(size)
	{
		case 1:
			if (mapData[x][y] != nullptr)
			{
				return mapData[x][y]->getBuilding() == nullptr;
			}
			else
			{
				return false;
			}
			break;
			
		case 2:
			return( hasRoom(x, y, 1) &&
				hasRoom(x - 1, y, 1) &&
				hasRoom(x, y - 1 , 1) &&
				hasRoom(x - 1, y - 1, 1) );
			break;
			
		case 3:
			return( hasRoom(x, y, 2) &&
				hasRoom(x - 2, y, 1) &&
				hasRoom(x - 2, y - 1, 1) &&
				hasRoom(x - 2, y - 2, 1) &&
				hasRoom(x - 1 , y - 2, 1) &&
				hasRoom(x, y - 2, 1) );
			break;
			
		case 4:
			return( hasRoom(x, y, 2) &&
				hasRoom(x - 2, y, 2) &&
				hasRoom(x, y - 2, 2) &&
				hasRoom(x - 2, y - 2, 2) );
			break;
	}
}

void Map::newTile(int x, int y, Tile::Terrain terrain)
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		std::cout << "newTile : (" << x << ", " << y << ") : This is beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] != nullptr)
	{
		std::cout << "newTile : (" << x << ", " << y << ") : There is alrady a " << dictTerrainString(mapData[x][y]->getTerrain()) << " tile here" << std::endl;
	}
	else
	{
		invalidateZone(x, y, 1);
		mapData[x][y] = new Tile(this, x, y, terrain);
		std::cout << "newTile : (" << x << ", " << y << ") : " << dictTerrainString(mapData[x][y]->getTerrain()) << " tile created" << std::endl;
	}
}

void Map::newTileArea(int x1, int y1, int x2, int y2, Tile::Terrain terrain)
{
	int xm = min(x1, x2);
	int xM = max(x1, x2);
	int ym = min(y1, y2);
	int yM = max(y1, y2);
	int i;
	int j;
	for (i = xm; i <= xM; i++)
	{
		for (j = ym; j <= yM; j++)
		{
			newTile(i, j, terrain);
		}
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

void Map::invalidateZone(int x, int y, int size)
{
	auto win = container->get_window();
		if (win)
		{
			Gdk::Rectangle r(
				isoToScreenX(x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight*TILE_WIDTH, 0) - size*TILE_WIDTH,
				isoToScreenY(x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight*TILE_WIDTH, 0) - 2*(size-1)*TILE_HEIGHT,
				2*size*TILE_WIDTH,
				2*size*TILE_HEIGHT
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
		std::cout << "printTile : (" << x << ", " << y << ") : This is beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] == nullptr)
	{
		std::cout << "printTile : (" << x << ", " << y << ") : No tile here" << std::endl;
	}
	else
	{
		std::cout << "printTile : (" << x << ", " << y << ") : " << mapData[x][y] << " : " << dictTerrainString(mapData[x][y]->getTerrain()) << " tile"<<std::endl;
	}
}

void Map::deleteTile(int x, int y)
{
	if(x >= mapWidth || y >= mapHeight || x < 0 || y <0)
	{
		std::cout << "deleteTile : (" << x << ", " << y << ") : This is beyond the map limits" << std::endl;
	}
	else if(mapData[x][y] == nullptr)
	{
		std::cout << "deleteTile : (" << x << ", " << y << ") : There is no tile here" << std::endl;
	}
	else
	{
		std::string terrainString = dictTerrainString(mapData[x][y]->getTerrain());
		delete mapData[x][y];
		mapData[x][y] = nullptr;
		invalidateZone(x, y, 1);
		std::cout << "deleteTile : (" << x << ", " << y << ") : " << terrainString << " tile deleted" << std::endl;
	}
}

void Map::deleteTileArea(int x1, int y1, int x2, int y2)
{
	int xm = min(x1, x2);
	int xM = max(x1, x2);
	int ym = min(y1, y2);
	int yM = max(y1, y2);
	int i;
	int j;
	for (i = xm; i <= xM; i++)
	{
		for (j = ym; j <= yM; j++)
		{
			deleteTile(i, j);
		}
	}
}

void Map::buildArea(int x1, int y1, int x2, int y2, Building::Type type)
{
	if (dictPolyBuildable(type))
	{
		int xm = min(x1, x2);
		int xM = max(x1, x2);
		int ym = min(y1, y2);
		int yM = max(y1, y2);
		int i;
		int j;
		for (i = xm; i <= xM; i++)
		{
			for (j = ym; j <= yM; j++)
			{
				if (mapData[i][j] != nullptr)
				{
					mapData[i][j]->newBuilding(type);
				}
			}
		}
	}
	else
	{
		if (mapData[x2][y2] != nullptr)
		{
			mapData[x2][y2]->newBuilding(type);
		}
	}
}

void Map::destroyArea(int x1, int y1, int x2, int y2)
{
	int xm = min(x1, x2);
	int xM = max(x1, x2);
	int ym = min(y1, y2);
	int yM = max(y1, y2);
	int i;
	int j;
	for (i = xm; i <= xM; i++)
	{
		for (j = ym; j <= yM; j++)
		{
			if (mapData[i][j] != nullptr)
			{
				mapData[i][j]->destroyBuilding();
			}
		}
	}
}

std::string dictEditModeString(int editMode)
{
	if (editMode == 0)
	{
		return "tile";
	}
	else
	{
		return "building";
	}
}



