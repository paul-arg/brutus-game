public class Brutus.Prefecture : Brutus.Building {
    private static Gdk.Pixbuf sprite;

    construct {
        if (sprite == null) {
            try {
                sprite = new Gdk.Pixbuf.from_file_at_size ("%s/sprites/prefecture.svg".printf (Build.BRUTUSDIR), TILE_WIDTH*2, -1);
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
        cr.set_source_rgb (0.6, 0.6, 0.6);
        var size = get_size ();
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
        return false;
    }

    public override int get_size () {
        return 1;
    }

    public override void build (Brutus.Tile support) {
        if (this.support != null) {
            critical ("Already built!");
            return;
        }

        this.support = support;
    }
}

