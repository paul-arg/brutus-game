public class Brutus.House : Brutus.Building {
    private static Gdk.Pixbuf sprite;
    public House (Brutus.Tile supportInput, Brutus.Building.Type typeInput) {
        support = supportInput;
        type = typeInput;
    }

    construct {
        if (sprite == null) {
            try {
                sprite = new Gdk.Pixbuf.from_file_at_size ("%s/sprites/house.svg".printf (Build.BRUTUSDIR), 64, -1);
            } catch (Error e) {
                critical (e.message);
            }
        }
    }

    public override void draw (Cairo.Context cr) {
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
        Gdk.cairo_set_source_pixbuf (cr, sprite, mapHeight * TILE_WIDTH + a - sprite.width/2, 2 * TILE_HEIGHT + b - sprite.height);
        cr.paint ();
    }

    public override int get_real_height () {
        return sprite.height;
    }

    public override bool is_poly_buildable () {
        return true;
    }

    public override int get_size () {
        return 1;
    }
}

