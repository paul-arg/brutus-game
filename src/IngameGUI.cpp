#include <iostream>
#include <gtkmm.h>

#include "GameView.hpp"
#include "IngameGUI.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"
#include "basicFunctions.hpp"

IngameGUI::IngameGUI()
: b1("Grass"),
b2("Forest"),
b3("Farmable"),
b4("Rock"),
b5("Water"),
b6("Fish"),
b7("Tiles"),
b8("Building")
{
	Gtk::RadioButton::Group group = b1.get_group();
	b2.set_group(group);
	b3.set_group(group);
	b4.set_group(group);
	b5.set_group(group);
	b6.set_group(group);

	Gtk::RadioButton::Group group2 = b7.get_group();
	b8.set_group(group2);

	b1.set_mode(false);
	b2.set_mode(false);
	b3.set_mode(false);
	b4.set_mode(false);
	b5.set_mode(false);
	b6.set_mode(false);
	b7.set_mode(false);
	b8.set_mode(false);

	b7.set_margin_top(6);
	b8.set_margin_top(6);


	set_border_width(10);
	set_halign(Gtk::ALIGN_END);

	b1.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b1, Tile::Terrain::GRASS));
	b2.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b2, Tile::Terrain::FOREST));
	b3.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b3, Tile::Terrain::FARMABLE));
	b4.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b4, Tile::Terrain::ROCK));
	b5.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b5, Tile::Terrain::WATER));
	b6.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), &b6, Tile::Terrain::FISH));
	b7.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, int>(sigc::mem_fun(*this, &IngameGUI::sendArchitect), &b7, 0));
	b8.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, int>(sigc::mem_fun(*this, &IngameGUI::sendArchitect), &b8, 1));

	attach(b1, 0, 0, 1, 1);
	attach(b2, 1, 0, 1, 1);
	attach(b3, 0, 1, 1, 1);
	attach(b4, 1, 1, 1, 1);
	attach(b5, 0, 2, 1, 1);
	attach(b6, 1, 2, 1, 1);
	attach(b7, 0, 3, 1, 1);
	attach(b8, 1, 3, 1, 1);
}

void IngameGUI::sendBrush(Gtk::RadioButton* button, Tile::Terrain data)
{
	if(!button->get_active())
		return;
	associatedGameView->setBrush(data);
	std::cout << "Brush set to " << getTerrainString(data) << std::endl;
}

void IngameGUI::sendArchitect(Gtk::RadioButton* button, int data)
{
	if(!button->get_active())
		return;
	b1.set_sensitive(b7.get_active());
	b2.set_sensitive(b7.get_active());
	b3.set_sensitive(b7.get_active());
	b4.set_sensitive(b7.get_active());
	b5.set_sensitive(b7.get_active());
	b6.set_sensitive(b7.get_active());
	associatedGameView->setArchitect(data);
	std::cout << "Architect set to " << data << std::endl;
	
}

void IngameGUI::associateGameView(GameView* gameViewInput)
{
	associatedGameView = gameViewInput;
}
