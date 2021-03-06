public class Brutus.Map : GLib.Object {

    public int mapHeight { public get; private set; }
    public int mapWidth { public get; private set; }
    private HashTable<int, Tile> mapData;
    public unowned MainWindow container;

    public Map (MainWindow containerInput, int mapWidthInput, int mapHeightInput) {
        container = containerInput;
        mapHeight = mapHeightInput;
        mapWidth = mapWidthInput;
        for (int x = 0; x < mapHeight; x++) {
            for (int y = 0; y < mapWidth; y++) {
                newTile (Tile.Terrain.GRASS, x, y);
            }
        }
    }

    construct {
        mapData = new HashTable<int, Tile> (direct_hash, direct_equal);
    }

    public bool beyondLimits (int x, int y) {
        return x >= mapWidth || y >= mapHeight || x < 0 || y < 0;
    }

    public void newTile (Tile.Terrain terrainInput, int x, int y) {
        if (beyondLimits (x, y)) {
            message (@"newTile : this is beyond the map limits.");
        } else {
            var tile = new Tile (this, x, y, terrainInput);
            mapData.set (x + y * mapWidth, tile);
            message (@"newTile : ($x, $y) : $(terrainInput.to_string()) tile created.");
            invalidateZone (x, y, 1);
        }
    }

    public unowned Tile ? getTile (int x, int y)
    {
        return mapData.get (x + y * mapWidth);
    }

    public bool hasRoom (int x, int y, int size) {
        /*
         * check if there is no building in the square of size "size"
         * support tile is the bottom tile of the square
         */

        switch (size) {
            case 1 :

                if (getTile (x, y) != null) {
                    return getTile (x, y).building == null;
                } else {
                    return false;
                }

            case 2:
                return (hasRoom (x, y, 1) &&
                        hasRoom (x - 1, y, 1) &&
                        hasRoom (x, y - 1, 1) &&
                        hasRoom (x - 1, y - 1, 1));

            case 3:
                return (hasRoom (x, y, 2) &&
                        hasRoom (x - 2, y, 1) &&
                        hasRoom (x - 2, y - 1, 1) &&
                        hasRoom (x - 2, y - 2, 1) &&
                        hasRoom (x - 1, y - 2, 1) &&
                        hasRoom (x, y - 2, 1));

            case 4:
                return (hasRoom (x, y, 2) &&
                        hasRoom (x - 2, y, 2) &&
                        hasRoom (x, y - 2, 2) &&
                        hasRoom (x - 2, y - 2, 2));

            default:
                return false;
        }
    }

    public bool farmableArea (int x, int y, int size) {
        /*
         * check if the square of size "size" is fully farmable
         * support tile is the bottom tile of the square
         */

        switch (size) {
            case 1:

                if (getTile (x, y) != null) {
                    return getTile (x, y).terrain == Tile.Terrain.FARMABLE;
                } else {
                    return false;
                }

            case 2:
                return (farmableArea (x, y, 1) &&
                        farmableArea (x - 1, y, 1) &&
                        farmableArea (x, y - 1, 1) &&
                        farmableArea (x - 1, y - 1, 1));

            case 3:
                return (farmableArea (x, y, 2) &&
                        farmableArea (x - 2, y, 1) &&
                        farmableArea (x - 2, y - 1, 1) &&
                        farmableArea (x - 2, y - 2, 1) &&
                        farmableArea (x - 1, y - 2, 1) &&
                        farmableArea (x, y - 2, 1));

            case 4:
                return (farmableArea (x, y, 2) &&
                        farmableArea (x - 2, y, 2) &&
                        farmableArea (x, y - 2, 2) &&
                        farmableArea (x - 2, y - 2, 2));

            default:
                return false;
        }
    }

    public void newTileArea (int x1, int y1, int x2, int y2, Tile.Terrain terrain) {
        int xm = int.min (x1, x2);
        int xM = int.max (x1, x2);
        int ym = int.min (y1, y2);
        int yM = int.max (y1, y2);
        int i;
        int j;

        for (i = xm; i <= xM; i++) {
            for (j = ym; j <= yM; j++) {
                newTile (terrain, i, j);
            }
        }
    }

    public void fillWith (Tile.Terrain paint) {
        for (int i = 0; i < mapWidth; i++) {
            for (int j = 0; j < mapHeight; j++) {
                if (getTile (i, j) == null) {
                    newTile (paint, i, j);
                    invalidateZone (i, j, 1);
                }
            }
        }
    }

    private void building_changed (Tile support) {
        unowned Tile tile = support.container.getTile (support.x-1, support.y);
        if (tile != null && tile.building != null) {
            tile.building.nighboor_buildings_changed ();
        }

        tile = support.container.getTile (support.x+1, support.y);
        if (tile != null && tile.building != null) {
            tile.building.nighboor_buildings_changed ();
        }

        tile = support.container.getTile (support.x, support.y-1);
        if (tile != null && tile.building != null) {
            tile.building.nighboor_buildings_changed ();
        }

        tile = support.container.getTile (support.x, support.y+1);
        if (tile != null && tile.building != null) {
            tile.building.nighboor_buildings_changed ();
        }
    }

    public void deleteTile (int x, int y) {
        if (beyondLimits (x, y)) {
            message (@"deleteTile : this is beyond the map limits.");
        } else if (getTile (x, y) == null) {
            message (@"deleteTile : ($x, $y) : there is no tile to delete here.");
        } else {
            message (@"deleteTile : ($x, $y) : $(getTile(x, y).terrain.to_string()) tile deleted.");
            mapData.remove (x + y * mapWidth);
            invalidateZone (x, y, 1);
        }
    }

    public void deleteTileArea (int x1, int y1, int x2, int y2) {
        int xm = int.min (x1, x2);
        int xM = int.max (x1, x2);
        int ym = int.min (y1, y2);
        int yM = int.max (y1, y2);
        int i;
        int j;

        for (i = xm; i <= xM; i++) {
            for (j = ym; j <= yM; j++) {
                deleteTile (i, j);
            }
        }
    }

    public void buildArea (int x1, int y1, int x2, int y2, Type type) {
        var needed_building = (Brutus.Building) GLib.Object.new (type, null);
        if (needed_building.is_poly_buildable) {
            int xm = int.min (x1, x2);
            int xM = int.max (x1, x2);
            int ym = int.min (y1, y2);
            int yM = int.max (y1, y2);
            int i;
            int j;

            for (i = xm; i <= xM; i++) {
                for (j = ym; j <= yM; j++) {
                    var tile = getTile (i, j);
                    if (beyondLimits (i, j)) {
                        message (@"build : this is beyond the map limits.");
                    } else if (tile == null) {
                        message (@"build : ($i, $j) : there is no tile here.");
                    } else {
                        var building = (Brutus.Building) GLib.Object.new (type);
                        tile.build (building);
                        building_changed (tile);
                    }
                }
            }
        } else {
            var tile = getTile (x2, y2);
            if (beyondLimits (x2, y2)) {
                message (@"build : this is beyond the map limits.");
            } else if (tile == null) {
                message (@"build : ($x2, $y2) : there is no tile here.");
            } else {
                tile.build (needed_building);
                building_changed (tile);
            }
        }
    }

    public void destroyArea (int x1, int y1, int x2, int y2) {
        int xm = int.min (x1, x2);
        int xM = int.max (x1, x2);
        int ym = int.min (y1, y2);
        int yM = int.max (y1, y2);
        int i;
        int j;

        for (i = xm; i <= xM; i++) {
            for (j = ym; j <= yM; j++) {
                var tile = getTile (i, j);
                if (tile == null) {
                    debug (@"destroyBuilding : ($i, $j) : there is no tile here.");
                } else {
                    tile.destroyBuilding ();
                    building_changed (tile);
                }
            }
        }
    }

    public void invalidateZone (int x, int y, int size) {
        container.game_view.queue_draw_area (
            isoToScreenX (x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight * TILE_WIDTH, 0) - size * TILE_WIDTH,
            isoToScreenY (x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight * TILE_WIDTH, 0) - 2 * (size - 1) * TILE_HEIGHT,
            2 * size * TILE_WIDTH,
            2 * size * TILE_HEIGHT
            );
    }

    public void invalidateBuilding (int x, int y, int size, int real_height) {
        container.game_view.queue_draw_area (
            isoToScreenX (x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight * TILE_WIDTH, 0) - size * TILE_WIDTH,
            isoToScreenY (x, y, TILE_HEIGHT, TILE_WIDTH, mapHeight * TILE_WIDTH, 0) + 2 * TILE_HEIGHT - real_height,
            2 * size * TILE_WIDTH,
            real_height
            );
    }

    public void drawGrid (Cairo.Context cr) {
        int i;
        cr.set_line_width (0.25);
        cr.set_source_rgb (0, 0, 0); /* black */

        for (i = 0; i <= mapWidth; i++) {
            int iTileWidth = i * TILE_WIDTH;
            int iTileHeight = i * TILE_HEIGHT;
            cr.move_to (0 + iTileWidth, mapHeight * TILE_HEIGHT + iTileHeight);
            cr.line_to (mapHeight * TILE_WIDTH + iTileWidth, iTileHeight);
            cr.stroke ();
        }

        for (i = 0; i <= mapHeight; i++) {
            int iTileWidth = i * TILE_WIDTH;
            int iTileHeight = i * TILE_HEIGHT;
            cr.move_to (0 + iTileWidth, mapHeight * TILE_HEIGHT - iTileHeight);
            cr.line_to (mapWidth * TILE_WIDTH + iTileWidth, mapHeight * TILE_HEIGHT + mapWidth * TILE_HEIGHT - iTileHeight);
            cr.stroke ();
        }
    }
}
