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
		void sendTileBrush(Gtk::RadioButton* button, Tile::Terrain data);
		void sendBuildingBrush(Gtk::RadioButton* button, Building::Type data);
		void sendEditMode(Gtk::RadioButton* button, int data);

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
		Gtk::RadioButton b11;
		Gtk::RadioButton b12;
		Gtk::RadioButton b13;
		GameView* associatedGameView;
};

#endif
