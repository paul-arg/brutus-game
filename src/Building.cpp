#include <iostream>
#include <cmath>

#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"

Building::Building(Tile* supportInput, Building::Type typeInput)
{
	support = supportInput;
	type = typeInput;
}

void Building::draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	int t = 5;
	int u = floor((t * TILE_WIDTH) / TILE_HEIGHT);
	int mapHeight = support->getContainer()->getHeight();
	int mapWidth = support->getContainer()->getWidth();
	int a = support->getX()*TILE_WIDTH - support->getY()*TILE_WIDTH; //offset x
	int b = support->getX()*TILE_HEIGHT + support->getY()*TILE_HEIGHT; //offset y
	
	cr->set_source_rgb(0.6, 0.6, 0.6);
	cr->move_to(mapHeight*TILE_WIDTH + a, 0 + b + t);
	cr->line_to(mapHeight*TILE_WIDTH + TILE_WIDTH + a - u, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a, 2*TILE_HEIGHT + b - t);
	cr->line_to(mapHeight*TILE_WIDTH - TILE_WIDTH + a + u, TILE_HEIGHT + b);
	cr->line_to(mapHeight*TILE_WIDTH + a, 0 + b + t);
	cr->fill();
}
 
