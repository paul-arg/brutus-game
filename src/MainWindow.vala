using Gtk;

public class Brutus.MainWindow : Window {
    public Map game_map;
    public GameView game_view;
    public InGameGUI game_GUI;

    public Tile.Terrain tileBrush;
    public int editMode;
    public Type buildingBrush;

    public MainWindow (int widthInput, int heightInput) {
        title = "brutus-game";
        window_position = WindowPosition.CENTER;
        set_default_size (850, 550);
        destroy.connect (Gtk.main_quit);

        var grid = new Grid ();
        grid.orientation = Gtk.Orientation.HORIZONTAL;

        game_view = new GameView (this);
        game_GUI = new InGameGUI (this);
        game_map = new Map (this, widthInput, heightInput);
        var scrolled_window = new Gtk.ScrolledWindow (null, null);
        scrolled_window.expand = true;
        scrolled_window.add_with_viewport (game_view);

        game_view.hexpand = true;
        game_view.vexpand = true;

        grid.add (scrolled_window);
        grid.add (game_GUI);

        add (grid);

        tileBrush = Tile.Terrain.GRASS;
        buildingBrush = typeof(Road);
        editMode = 1;

        /* testing */
        game_map.newTile (Tile.Terrain.FOREST, 2, 5);
        game_map.buildArea (2, 5, 2, 5, typeof(Road));
    }

    public static int main (string[] args) {
        Gtk.init (ref args);

        var window = new Brutus.MainWindow (20, 20);
        window.show_all ();

        Gtk.main ();
        return 0;
    }
}
