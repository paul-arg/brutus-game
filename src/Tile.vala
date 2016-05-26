public class Tile {
	public enum Terrain {
		GRASS,
		FARMABLE,
		WATER,
		FISH,
		ROCK,
		FOREST;

		public string to_string() {
			switch (this) {
				case GRASS:
					return "grass";

				case FARMABLE:
					return "farmable";

				case WATER:
					return "water";

				case FISH:
					return "fish";

				case ROCK:
					return "rock";

				case FOREST:
					return "forest";

				default:
					assert_not_reached();
			}
		}

		public bool buildable() {
			switch (this) {
				case GRASS:
					return true;

				case FARMABLE:
					return true;

				default:
					return false;
			}
		}
	}

	public unowned Map container {public get; private set;}
	public int x {public get; private set;}
	public int y {public get; private set;}
	public Tile.Terrain terrain {public get; private set;}
	public Building? building {public get; private set;}

	public Tile(Map containerInput, int xInput, int yInput, Tile.Terrain terrainInput)
	{
		container = containerInput;
		x = xInput;
		y = yInput;
		terrain = terrainInput;
		building = null;
	}

	public void setBuilding(Building buildingInput)
	{
		building = buildingInput;
		container.invalidateZone(x, y, 1);
	}

	public void build(Building.Type typeInput)
	{
		if(!container.hasRoom(x, y, typeInput.size()))
		{
			stdout.printf(@"build : ($x, $y) : there is no room for this building.\n");
		}
		else if (!container.farmableArea(x, y, typeInput.size())) {
			stdout.printf(@"build : ($x, $y) : farms can only be built on farmable areas.\n");
		}
		else if(!terrain.buildable())
			stdout.printf(@"build : ($x, $y) : this terrain is not buildable.\n");
		else
		{
			building = new Building(this, typeInput);
			int i;
			int j;
			for (i = 0; i < typeInput.size(); i++)
			{
				for (j = 0; j < typeInput.size(); j++)
				{
					container.getTile(x - i, y - j).setBuilding(building);
				}
			}
			stdout.printf(@"build : ($x, $y) : $(typeInput.to_string()) created.\n");
			container.invalidateZone(x, y, typeInput.size());
		}
	}

	public void destroyBuilding()
	{
		if (building == null)
		{
			stdout.printf(@"destroyBuilding : ($x, $y) : there is no building to destroy here.\n");
		}
		else
		{
			var size = building.type.size();
			var type = building.type;
			var xS = building.support.x;
			var yS = building.support.y;
			int i;
			int j;
			for (i = 0; i < size; i++)
			{
				for (j = 0; j < size; j++)
				{
					container.getTile(xS - i, yS - j).building = null;
				}
			}
			stdout.printf(@"destroyBuilding : ($xS, $yS) : $(type.to_string()) destroyed.\n");
			container.invalidateZone(xS, yS, size);
		}
	}

	public void draw(Cairo.Context cr)
	{
		int mapHeight = container.mapHeight;
		int a = x*TILE_WIDTH - y*TILE_WIDTH; //offset x
		int b = x*TILE_HEIGHT + y*TILE_HEIGHT; //offset y
		switch(terrain)
		{
			case Tile.Terrain.GRASS:
				cr.set_source_rgb(0.20,0.73,0.13);
				break;
			case Tile.Terrain.FARMABLE:
				cr.set_source_rgb(1, 0.7, 0);
				break;
			case Tile.Terrain.WATER:
				cr.set_source_rgb(0.19,0.55,0.80);
				break;
			case Tile.Terrain.FISH:
				cr.set_source_rgb(0.11,0.42,0.64);
				break;
			case Tile.Terrain.ROCK:
				cr.set_source_rgb(0.5, 0.5, 0.5);
				break;
			case Tile.Terrain.FOREST:
				cr.set_source_rgb(0.07,0.57,0.19);
				break;
		}
		cr.move_to(mapHeight*TILE_WIDTH + a             , 0 + b);
		cr.line_to(mapHeight*TILE_WIDTH + TILE_WIDTH + a, TILE_HEIGHT + b);
		cr.line_to(mapHeight*TILE_WIDTH + a             , 2*TILE_HEIGHT + b);
		cr.line_to(mapHeight*TILE_WIDTH - TILE_WIDTH + a, TILE_HEIGHT + b);
		cr.line_to(mapHeight*TILE_WIDTH + a             , 0 + b);
		cr.fill();
	}

}
