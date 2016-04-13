#include <iostream>
#include <gtkmm.h>
#include <set>

#include "GameView.hpp"
#include "IngameGUI.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Building.hpp"
#include "basicFunctions.hpp"

using namespace std;

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "paul.game");

	Gtk::Window win;
	win.set_title("Game");
	win.set_default_size(1600, 700);
	win.set_size_request(1600, 700);

	Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	win.add(*vbox);

	GameView gameView;
	IngameGUI ingameGUI;

	vbox->add(gameView);
	vbox->add(ingameGUI);
	vbox->show_all();

	Map map(20, 20);

	gameView.addMap(&map);
	ingameGUI.associateGameView(&gameView);

	map.fillWith(Tile::Terrain::GRASS);
	map.getTile(3, 5)->newBuilding(Building::Type::HOUSE);
	map.getTile(3, 6)->newBuilding(Building::Type::HOUSE);
	map.getTile(3, 7)->newBuilding(Building::Type::HOUSE);
	map.getTile(3, 8)->newBuilding(Building::Type::HOUSE);
	map.getTile(3, 9)->newBuilding(Building::Type::HOUSE);


	return app->run(win);
}

