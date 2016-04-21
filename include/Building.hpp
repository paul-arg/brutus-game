#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>

class Tile;

class Building
{
	public:
		enum Type {ROAD, HOUSE, FOUNTAIN, MARKET, FARM};

		Building(Tile* supportInput, Building::Type typeInput);
		~Building();

		void draw(const Cairo::RefPtr<Cairo::Context>& cr);

		Tile* getSupport() const;
		int getSize() const;
		Building::Type getType();
		bool isPolyBuildable();

	private:
		Tile* support;
		Building::Type type;
		int size;
		bool polyBuildable;
		int employeesNeeded;
		int employees;
		int houseLevel;
		int inhabitantsMax;
		int inhabitants;
};

int dictBuildingSize(Building::Type);
bool dictPolyBuildable(Building::Type);
std::string dictBuildingString(Building::Type building);

#endif
