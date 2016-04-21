#include <iostream>
#include <cmath>
#include <gtkmm.h>

#include "GameView.hpp"
#include "IngameGUI.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"


using namespace std;

GameView::GameView() //constructor
{
	//signals
	add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	signal_button_press_event().connect( sigc::mem_fun( *this, &GameView::onMouseDown ) );
	signal_button_release_event().connect( sigc::mem_fun( *this, &GameView::onMouseUp ) );
	set_hexpand(true);
	set_vexpand(true);
	map = nullptr;
	tileBrush = Tile::Terrain::GRASS;
	buildingBrush = Building::Type::ROAD;
	editMode = 0;
}

void GameView::setTileBrush(Tile::Terrain tileBrushInput)
{
	tileBrush = tileBrushInput;
}

void GameView::setBuildingBrush(Building::Type buildingBrushInput)
{
	buildingBrush = buildingBrushInput;
}

void GameView::setEditMode(int editModeInput)
{
	editMode = editModeInput;
}

bool GameView::onMouseDown( GdkEventButton *event )
{
	xIsoClick = screenToIsoX(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	yIsoClick = screenToIsoY(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	//cout << "    clicked at " << event->x << ", " << event->y << endl;
	//cout << "    clicked at iso " << xIso << ", " << yIso << endl;
	
	return true;
}

bool GameView::onMouseUp( GdkEventButton *event )
{
	int xIsoRelease = screenToIsoX(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	int yIsoRelease = screenToIsoY(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	//cout << "    released at " << event->x << ", " << event->y << endl;
	//cout << "    released at iso " << xIso << ", " << yIso << endl;*/
	if (editMode == 0)
	{
		if(map != nullptr)
		{
		if(event->button == 1)
			map->newTileArea(xIsoClick, yIsoClick, xIsoRelease, yIsoRelease, tileBrush);
		if(event->button == 3)
			map->deleteTileArea(xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
		}
	}
	if (editMode == 1)
	{
		if (map->getTile(xIsoRelease, yIsoRelease) != nullptr)
		{
			if(event->button == 1)
			{
				map->buildArea(xIsoClick, yIsoClick, xIsoRelease, yIsoRelease, buildingBrush);
			}
			if(event->button == 3)
			{
				map->destroyArea(xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
			}
		}
	}

	return true;
}

void GameView::addMap(Map* mapInput)
{
	map = mapInput;
	map->setContainer(this);
}

bool GameView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	if(map != nullptr)
	{
		cr->set_line_width(3.0);
		int i, j;
		for(i = 0; i < map->getWidth(); i++)
		{
			for(j = 0; j < map->getHeight(); j++)
			{
				if(map->getTile(i, j) != nullptr)
				{
					map->getTile(i, j)->draw(cr);
					if (map->getTile(i, j)->getBuilding() != nullptr)
					{
						map->getTile(i, j)->getBuilding()->draw(cr);
					}
				}
			}
		}
		cr->set_line_width(3.0);
		map->drawGrid(cr);
	}

	return true;
}

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





