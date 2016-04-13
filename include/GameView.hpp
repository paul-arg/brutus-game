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

		void addMap(Map* mapInput);
		void setBrush(Tile::Terrain brushInput);
		void setArchitect(int architectInput);

	protected:
		//Override default signal handler:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
		Map* map;
		Tile::Terrain brush;
		int architect;
};

#endif
