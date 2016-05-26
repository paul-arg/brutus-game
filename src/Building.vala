public class Building {
    public enum Type {
        ROAD,
        HOUSE,
        FOUNTAIN,
        MARKET,
        FARM;

        public string to_string () {
            switch (this) {
                case ROAD:
                    return "road";

                case HOUSE:
                    return "house";

                case FOUNTAIN:
                    return "fountain";

                case MARKET:
                    return "market";

                case FARM:
                    return "farm";

                default:
                    assert_not_reached ();
            }
        }

        public bool poly_buildable () {
            switch (this) {
                case ROAD:
                    return true;

                case HOUSE:
                    return true;

                default:
                    return false;
            }
        }

        public int size () {
            switch (this) {
                case ROAD:
                    return 1;

                case HOUSE:
                    return 1;

                case FOUNTAIN:
                    return 1;

                case MARKET:
                    return 2;

                case FARM:
                    return 3;

                default:
                    assert_not_reached ();
            }
        }
    }

    public Building.Type type;
    public Tile support;

    public Building (Tile supportInput, Building.Type typeInput) {
        support = supportInput;
        type = typeInput;
    }

    public void draw (Cairo.Context cr) {
        int t = 5;
        int u = (int)Math.floor ((t * TILE_WIDTH) / TILE_HEIGHT);
        int mapHeight = support.container.mapHeight;
        int a = support.x * TILE_WIDTH - support.y * TILE_WIDTH; /* offset x */
        int b = support.x * TILE_HEIGHT + support.y * TILE_HEIGHT; /* offset y */

        if (type == Building.Type.ROAD) {
            cr.set_source_rgb (1, 0, 0);
        } else {
            cr.set_source_rgb (0.6, 0.6, 0.6);
        }

        var size = type.size ();
        cr.move_to (mapHeight * TILE_WIDTH + a, 2 * TILE_HEIGHT + b - t);
        cr.line_to (mapHeight * TILE_WIDTH + a + size * TILE_WIDTH - u, 2 * TILE_HEIGHT + b - size * TILE_HEIGHT);
        cr.line_to (mapHeight * TILE_WIDTH + a, 2 * TILE_HEIGHT + b - 2 * size * TILE_HEIGHT + t);
        cr.line_to (mapHeight * TILE_WIDTH + a - size * TILE_WIDTH + u, 2 * TILE_HEIGHT + b - size * TILE_HEIGHT);
        cr.line_to (mapHeight * TILE_WIDTH + a, 2 * TILE_HEIGHT + b - t);
        cr.fill ();
    }
}