public abstract class Brutus.Building : GLib.Object {
    public Tile support;
    public bool is_poly_buildable { get; internal set construct; default = false; }
    public int size { get; internal set construct; default = 1; }
    public signal void nighboor_buildings_changed ();
    public signal void queue_redraw ();

    public abstract void draw (Cairo.Context cr);
    public abstract int get_real_height ();
    public abstract void build (Brutus.Tile support);
}
