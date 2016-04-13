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

	b1.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::GRASS));
	b2.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::FOREST));
	b3.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::FARMABLE));
	b4.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::ROCK));
	b5.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::WATER));
	b6.signal_clicked().connect(sigc::bind<Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendBrush), Tile::Terrain::FISH));
	b7.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &IngameGUI::sendArchitect), 0));
	b8.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &IngameGUI::sendArchitect), 1));

	attach(b1, 0, 0, 1, 1);
	attach(b2, 1, 0, 1, 1);
	attach(b3, 0, 1, 1, 1);
	attach(b4, 1, 1, 1, 1);
	attach(b5, 0, 2, 1, 1);
	attach(b6, 1, 2, 1, 1);
	attach(b7, 0, 3, 1, 1);
	attach(b8, 1, 3, 1, 1);
}

void IngameGUI::sendBrush(Tile::Terrain data)
{
	associatedGameView->setBrush(data);
	std::cout << "Brush set to " << getTerrainString(data) << std::endl;
}

void IngameGUI::sendArchitect(int data)
{
	associatedGameView->setArchitect(data);
	std::cout << "Architect set to " << data << std::endl;
	
}

void IngameGUI::associateGameView(GameView* gameViewInput)
{
	associatedGameView = gameViewInput;
}
