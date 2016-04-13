#ifndef INGAME_GUI_HPP
#define INGAME_GUI_HPP

#include <iostream>
#include <gtkmm.h>

#include "GameView.hpp"
#include "Tile.hpp"

class IngameGUI : public Gtk::Grid
{
	public:
		IngameGUI();

		void associateGameView(GameView* gameViewInput);
		void sendBrush(Tile::Terrain data);
		void sendArchitect(int data);

	private:
		Gtk::RadioButton b1;
		Gtk::RadioButton b2;
		Gtk::RadioButton b3;
		Gtk::RadioButton b4;
		Gtk::RadioButton b5;
		Gtk::RadioButton b6;
		Gtk::RadioButton b7;
		Gtk::RadioButton b8;
		Gtk::RadioButton b9;
		Gtk::RadioButton b10;
		GameView* associatedGameView;
};

#endif
