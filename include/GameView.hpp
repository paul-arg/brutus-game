#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <iostream>
#include <gtkmm.h>

#include "Tile.hpp"
#include "Building.hpp"

class Map;

class GameView : public Gtk::DrawingArea
{
	public:
		GameView();

		bool onMouseDown( GdkEventButton *event );
		bool onMouseUp( GdkEventButton *event );

		void addMap(Map* mapInput);
		void setTileBrush(Tile::Terrain tileBrushInput);
		void setBuildingBrush(Building::Type buildingBrushInput);
		void setEditMode(int editModeInput);

	protected:
		//Override default signal handler:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
		Map* map;
		Tile::Terrain tileBrush;
		Building::Type buildingBrush;
		int editMode;
		int xIsoClick;
		int yIsoClick;
};

int screenToIsoX(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY);
int screenToIsoY(int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY);
int isoToScreenX(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY);
int isoToScreenY(int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY);

#endif
