#include <iostream>
#include <gtkmm.h>

#include "GameView.hpp"
#include "IngameGUI.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"


IngameGUI::IngameGUI()
: b1("Grass"),
b2("Forest"),
b3("Farmable"),
b4("Rock"),
b5("Water"),
b6("Fish"),
b7("Tiles"),
b8("Building"),
b9("Road"),
b10("House"),
b11("Fountain"),
b12("Market"),
b13("Farm")
{
	Gtk::RadioButton::Group tileBrushGroup = b1.get_group();
	b2.set_group(tileBrushGroup);
	b3.set_group(tileBrushGroup);
	b4.set_group(tileBrushGroup);
	b5.set_group(tileBrushGroup);
	b6.set_group(tileBrushGroup);

	Gtk::RadioButton::Group editModeGroup = b7.get_group();
	b8.set_group(editModeGroup);

	Gtk::RadioButton::Group buildingBrushGroup = b9.get_group();
	b10.set_group(buildingBrushGroup);
	b11.set_group(buildingBrushGroup);
	b12.set_group(buildingBrushGroup);
	b13.set_group(buildingBrushGroup);

	b1.set_mode(false);
	b2.set_mode(false);
	b3.set_mode(false);
	b4.set_mode(false);
	b5.set_mode(false);
	b6.set_mode(false);
	b7.set_mode(false);
	b8.set_mode(false);
	b9.set_mode(false);
	b10.set_mode(false);
	b11.set_mode(false);
	b12.set_mode(false);
	b13.set_mode(false);

	b9.set_sensitive(false);
	b10.set_sensitive(false);
	b11.set_sensitive(false);
	b12.set_sensitive(false);
	b13.set_sensitive(false);

	b7.set_margin_top(6);
	b8.set_margin_top(6);

	b7.set_margin_bottom(6);
	b8.set_margin_bottom(6);


	set_border_width(10);
	set_halign(Gtk::ALIGN_END);

	b1.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b1, Tile::Terrain::GRASS));
	b2.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b2, Tile::Terrain::FOREST));
	b3.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b3, Tile::Terrain::FARMABLE));
	b4.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b4, Tile::Terrain::ROCK));
	b5.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b5, Tile::Terrain::WATER));
	b6.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Tile::Terrain>(sigc::mem_fun(*this, &IngameGUI::sendTileBrush), &b6, Tile::Terrain::FISH));
	
	b7.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, int>(sigc::mem_fun(*this, &IngameGUI::sendEditMode), &b7, 0));
	b8.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, int>(sigc::mem_fun(*this, &IngameGUI::sendEditMode), &b8, 1));

	b9.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Building::Type>(sigc::mem_fun(*this, &IngameGUI::sendBuildingBrush), &b9, Building::Type::ROAD));
	b10.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Building::Type>(sigc::mem_fun(*this, &IngameGUI::sendBuildingBrush), &b10, Building::Type::HOUSE));
	b11.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Building::Type>(sigc::mem_fun(*this, &IngameGUI::sendBuildingBrush), &b11, Building::Type::FOUNTAIN));
	b12.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Building::Type>(sigc::mem_fun(*this, &IngameGUI::sendBuildingBrush), &b12, Building::Type::MARKET));
	b13.signal_toggled().connect(sigc::bind<Gtk::RadioButton*, Building::Type>(sigc::mem_fun(*this, &IngameGUI::sendBuildingBrush), &b13, Building::Type::FARM));

	attach(b1, 0, 0, 1, 1);
	attach(b2, 1, 0, 1, 1);
	attach(b3, 0, 1, 1, 1);
	attach(b4, 1, 1, 1, 1);
	attach(b5, 0, 2, 1, 1);
	attach(b6, 1, 2, 1, 1);
	attach(b7, 0, 3, 1, 1);
	attach(b8, 1, 3, 1, 1);
	attach(b9, 0, 4, 1, 1);
	attach(b10, 1, 4, 1, 1);
	attach(b11, 0, 5, 1, 1);
	attach(b12, 1, 5, 1, 1);
	attach(b13, 0, 6, 1, 1);
}

void IngameGUI::sendTileBrush(Gtk::RadioButton* button, Tile::Terrain data)
{
	if(!button->get_active())
		return;
	associatedGameView->setTileBrush(data);
	std::cout << "Tile brush set to " << dictTerrainString(data) << std::endl;
}

void IngameGUI::sendBuildingBrush(Gtk::RadioButton* button, Building::Type data)
{
	if(!button->get_active())
		return;
	associatedGameView->setBuildingBrush(data);
	std::cout << "Building brush set to " << dictBuildingString(data) << std::endl;
}

void IngameGUI::sendEditMode(Gtk::RadioButton* button, int data)
{
	if(!button->get_active())
		return;
	b1.set_sensitive(b7.get_active());
	b2.set_sensitive(b7.get_active());
	b3.set_sensitive(b7.get_active());
	b4.set_sensitive(b7.get_active());
	b5.set_sensitive(b7.get_active());
	b6.set_sensitive(b7.get_active());

	b9.set_sensitive(b8.get_active());
	b10.set_sensitive(b8.get_active());
	b11.set_sensitive(b8.get_active());
	b12.set_sensitive(b8.get_active());
	b13.set_sensitive(b8.get_active());
	
	associatedGameView->setEditMode(data);
	std::cout << "Edit mode set to " << dictEditModeString(data) << std::endl;
}

void IngameGUI::associateGameView(GameView* gameViewInput)
{
	associatedGameView = gameViewInput;
}
