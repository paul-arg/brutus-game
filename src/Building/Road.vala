public class Brutus.Road : Brutus.Building {
    private static Gdk.Pixbuf l_north_south;
    private static Gdk.Pixbuf l_east_west;
    private static Gdk.Pixbuf x_cross;
    private static Gdk.Pixbuf v_north_west;
    private static Gdk.Pixbuf v_north_east;
    private static Gdk.Pixbuf v_south_east;
    private static Gdk.Pixbuf v_south_west;
    private static Gdk.Pixbuf y_west;
    private static Gdk.Pixbuf y_north;
    private static Gdk.Pixbuf y_east;
    private static Gdk.Pixbuf y_south;
    private static Gdk.Pixbuf i_west;
    private static Gdk.Pixbuf i_north;
    private static Gdk.Pixbuf i_east;
    private static Gdk.Pixbuf i_south;
    private static Gdk.Pixbuf o_alone;

    private unowned Gdk.Pixbuf sprite;

    construct {
        if (l_north_south == null) {
            try {
                var sprite = new Gdk.Pixbuf.from_file_at_size ("%s/sprites/road.svg".printf (Build.BRUTUSDIR), TILE_WIDTH*2*16, -1);
                l_north_south = new Gdk.Pixbuf.subpixbuf (sprite, 0, 0, 2*TILE_WIDTH, sprite.height);
                l_east_west = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH, 0, 2*TILE_WIDTH, sprite.height);
                x_cross = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*2, 0, 2*TILE_WIDTH, sprite.height);
                v_north_west = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*3, 0, 2*TILE_WIDTH, sprite.height);
                v_north_east = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*4, 0, 2*TILE_WIDTH, sprite.height);
                v_south_east = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*5, 0, 2*TILE_WIDTH, sprite.height);
                v_south_west = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*6, 0, 2*TILE_WIDTH, sprite.height);
                y_west = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*7, 0, 2*TILE_WIDTH, sprite.height);
                y_north = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*8, 0, 2*TILE_WIDTH, sprite.height);
                y_east = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*9, 0, 2*TILE_WIDTH, sprite.height);
                y_south = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*10, 0, 2*TILE_WIDTH, sprite.height);
                i_west = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*11, 0, 2*TILE_WIDTH, sprite.height);
                i_north = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*12, 0, 2*TILE_WIDTH, sprite.height);
                i_east = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*13, 0, 2*TILE_WIDTH, sprite.height);
                i_south = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*14, 0, 2*TILE_WIDTH, sprite.height);
                o_alone = new Gdk.Pixbuf.subpixbuf (sprite, 2*TILE_WIDTH*15, 0, 2*TILE_WIDTH, sprite.height);
            } catch (Error e) {
                critical (e.message);
            }
        }

        sprite = o_alone;
    }

    public override void draw (Cairo.Context cr) {
        int mapHeight = support.container.mapHeight;
        int a = support.x * TILE_WIDTH - support.y * TILE_WIDTH; /* offset x */
        int b = support.x * TILE_HEIGHT + support.y * TILE_HEIGHT; /* offset y */

        Gdk.cairo_set_source_pixbuf (cr, sprite, mapHeight * TILE_WIDTH + a - sprite.width/2, 2 * TILE_HEIGHT + b - sprite.height);
        cr.paint ();
    }

    public override int get_real_height () {
        return l_north_south.height;
    }

    public override bool is_poly_buildable () {
        return true;
    }

    public override int get_size () {
        return 1;
    }

    private void nighboor_changed () {
        unowned Tile north_tile = support.container.getTile (support.x-1, support.y);
        unowned Tile south_tile = support.container.getTile (support.x+1, support.y);
        unowned Tile east_tile = support.container.getTile (support.x, support.y-1);
        unowned Tile west_tile = support.container.getTile (support.x, support.y+1);
        bool north_road = false;
        if (north_tile != null && north_tile.building != null) {
            if (north_tile.building is Brutus.Road) {
                north_road = true;
            }
        }

        bool south_road = false;
        if (south_tile != null && south_tile.building != null) {
            if (south_tile.building is Brutus.Road) {
                south_road = true;
            }
        }

        bool west_road = false;
        if (west_tile != null && west_tile.building != null) {
            if (west_tile.building is Brutus.Road) {
                west_road = true;
            }
        }

        bool east_road = false;
        if (east_tile != null && east_tile.building != null) {
            if (east_tile.building is Brutus.Road) {
                east_road = true;
            }
        }

        if (north_road && south_road && west_road && east_road) {
            sprite = x_cross;
        } else if (north_road && south_road && west_road && !east_road) {
            sprite = y_west;
        } else if (north_road && south_road && !west_road && east_road) {
            sprite = y_east;
        } else if (north_road && !south_road && west_road && east_road) {
            sprite = y_north;
        } else if (!north_road && south_road && west_road && east_road) {
            sprite = y_south;
        } else if (north_road && south_road && !west_road && !east_road) {
            sprite = l_north_south;
        } else if (north_road && !south_road && west_road && !east_road) {
            sprite = v_north_west;
        } else if (!north_road && south_road && west_road && !east_road) {
            sprite = v_south_west;
        } else if (!north_road && !south_road && west_road && east_road) {
            sprite = l_east_west;
        } else if (north_road && !south_road && !west_road && east_road) {
            sprite = v_north_east;
        } else if (!north_road && south_road && !west_road && east_road) {
            sprite = v_south_east;
        } else if (!north_road && south_road && !west_road && !east_road) {
            sprite = i_south;
        } else if (!north_road && !south_road && west_road && !east_road) {
            sprite = i_west;
        } else if (!north_road && !south_road && !west_road && east_road) {
            sprite = i_east;
        } else if (!north_road && !south_road && !west_road && !east_road) {
            sprite = o_alone;
        }
    }

    public override void build (Brutus.Tile support) {
        if (this.support != null) {
            critical ("Already built!");
            return;
        }

        this.support = support;
        nighboor_changed ();
        unowned Tile north_tile = support.container.getTile (support.x-1, support.y);
        unowned Tile south_tile = support.container.getTile (support.x+1, support.y);
        unowned Tile west_tile = support.container.getTile (support.x, support.y-1);
        unowned Tile east_tile = support.container.getTile (support.x, support.y+1);
        if (north_tile != null) {
            north_tile.notify["building"].connect (() => nighboor_changed ());
        }

        if (south_tile != null) {
            south_tile.notify["building"].connect (() => nighboor_changed ());
        }

        if (west_tile != null) {
            west_tile.notify["building"].connect (() => nighboor_changed ());
        }

        if (east_tile != null) {
            east_tile.notify["building"].connect (() => nighboor_changed ());
        }
    }
}

