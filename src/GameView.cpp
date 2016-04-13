#include <iostream>
#include <gtkmm.h>

#include "GameView.hpp"
#include "IngameGUI.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"
#include "basicFunctions.hpp"

using namespace std;

GameView::GameView() //constructor
{
	//signals
	add_events( Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	signal_button_press_event().connect( sigc::mem_fun( *this, &GameView::onMouseDown ) );
	set_hexpand(true);
	set_vexpand(true);
	map = nullptr;
	brush = Tile::Terrain::GRASS;
	architect = 0;
}

void GameView::setBrush(Tile::Terrain brushInput)
{
	brush = brushInput;
}

void GameView::setArchitect(int architectInput)
{
	architect = architectInput;
}

bool GameView::onMouseDown( GdkEventButton *event )
{
	int xIso = screenToIsoX(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	int yIso = screenToIsoY(event->x, event->y, TILE_HEIGHT, TILE_WIDTH, map->getHeight()*TILE_WIDTH, 0);
	cout << "    clicked at " << event->x << ", " << event->y << endl;
	cout << "    clicked at iso " << xIso << ", " << yIso << endl;
	if (architect == 0)
	{
		if(map != nullptr)
		{
		if(event->button == 1)
			map->newTile(xIso, yIso, brush);
		if(event->button == 3)
			map->deleteTile(xIso, yIso);
		}
	}
	if (architect == 1)
	{
		if (map->getTile(xIso, yIso) != nullptr)
		{
			if(event->button == 1)
			{
				map->getTile(xIso, yIso)->newBuilding(Building::Type::HOUSE);
			}
			if(event->button == 3)
			{
				map->getTile(xIso, yIso)->deleteBuilding();
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
//overriding the render function
{
	cr->set_line_width(3.0);

	if(map != nullptr)
	{
		map->drawGrid(cr);

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
	}

	return true;
}





