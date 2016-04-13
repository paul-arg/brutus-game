#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>

class Tile;

class Building
{
	public:
		enum Type {ROAD, SIGN, HOUSE, FOUNTAIN, MARKET, FARM};

		Building(Tile* supportInput, Building::Type typeInput);

		void draw(const Cairo::RefPtr<Cairo::Context>& cr);

		Tile* getSupport() const;

	private:
		Tile* support;
		Building::Type type;
		int employeesNeeded;
		int employees;
		int houseLevel;
		int inhabitantsMax;
		int inhabitants;
};

#endif
