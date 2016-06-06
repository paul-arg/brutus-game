public abstract class Brutus.Building : GLib.Object {
/*
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
                case HOUSE:
                    return true;

                default:
                    return false;
            }
        }

        public int size () {
            switch (this) {
                case ROAD:
                case HOUSE:
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
    }*/

    public Tile support;

    public abstract void draw (Cairo.Context cr);
    public abstract int get_real_height ();
    public abstract bool is_poly_buildable ();
    public abstract int get_size ();
    public abstract void build (Brutus.Tile support);
}
