using Gtk;

public class Brutus.MainWindow : Window {
    public Map game_map;
    public GameView game_view;
    public InGameGUI game_GUI;

    public Tile.Terrain tileBrush;
    public Brutus.Building.Type buildingBrush;
    public int editMode;

    public MainWindow (int widthInput, int heightInput) {
        title = "brutus-game";
        border_width = 10;
        window_position = WindowPosition.CENTER;
        set_default_size (850, 550);
        destroy.connect (Gtk.main_quit);

        var box = new Box (Gtk.Orientation.HORIZONTAL, 0);

        game_view = new GameView (this);
        game_GUI = new InGameGUI (this);
        game_map = new Map (this, widthInput, heightInput);

        game_view.hexpand = true;
        game_view.vexpand = true;

        box.add (game_view);
        box.add (game_GUI);

        add (box);

        tileBrush = Tile.Terrain.GRASS;
        buildingBrush = Building.Type.ROAD;
        editMode = 1;

        /* testing */
        game_map.newTile (Tile.Terrain.FOREST, 2, 5);
        game_map.getTile (2, 5).build (Building.Type.ROAD);
    }

    public static int main (string[] args) {
        Gtk.init (ref args);

        var window = new Brutus.MainWindow (20, 20);
        window.show_all ();

        Gtk.main ();
        return 0;
    }
}
