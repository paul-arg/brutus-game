
public class Brutus.InGameGUI : Gtk.Grid {
    private unowned MainWindow container;
    private Gtk.RadioButton grassButton;
    private Gtk.RadioButton forestButton;
    private Gtk.RadioButton farmableButton;
    private Gtk.RadioButton rockButton;
    private Gtk.RadioButton waterButton;
    private Gtk.RadioButton fishButton;

    private Gtk.RadioButton roadButton;
    private Gtk.RadioButton houseButton;
    private Gtk.RadioButton fountainButton;
    private Gtk.RadioButton marketButton;
    private Gtk.RadioButton farmButton;
    private Gtk.RadioButton prefectureButton;
    private Gtk.RadioButton engineerButton;

    public InGameGUI (MainWindow containerInput) {
        get_style_context ().add_class ("panel");
        var provider = new Gtk.CssProvider ();
        try {
            provider.load_from_data (custom_css, custom_css.length);
            Gtk.StyleContext.add_provider_for_screen (get_screen (), provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION);
        } catch (GLib.Error e) {
            critical (e.message);
        }

        Gtk.IconTheme.get_default ().append_search_path (GLib.Path.build_filename (Build.BRUTUSDIR, "menus"));
        container = containerInput;
        orientation = Gtk.Orientation.VERTICAL;
        var stack = new Gtk.Stack ();
        stack.margin = 6;
        stack.transition_type = Gtk.StackTransitionType.SLIDE_LEFT_RIGHT;
        var stack_switcher = new Gtk.StackSwitcher ();
        stack_switcher.margin = 12;
        stack_switcher.margin_bottom = 6;
        stack_switcher.set_stack (stack);

        var tile_grid = new Gtk.Grid ();
        tile_grid.orientation = Gtk.Orientation.VERTICAL;
        tile_grid.halign = Gtk.Align.CENTER;
        tile_grid.row_spacing = 6;
        tile_grid.margin_bottom = 6;
        grassButton = new Gtk.RadioButton.with_label (null, "Grass");
        forestButton = new Gtk.RadioButton.with_label_from_widget (grassButton, "Forest");
        farmableButton = new Gtk.RadioButton.with_label_from_widget (grassButton, "Farmable");
        rockButton = new Gtk.RadioButton.with_label_from_widget (grassButton, "Rock");
        waterButton = new Gtk.RadioButton.with_label_from_widget (grassButton, "Water");
        fishButton = new Gtk.RadioButton.with_label_from_widget (grassButton, "Fish");

        tile_grid.add (grassButton);
        tile_grid.add (forestButton);
        tile_grid.add (farmableButton);
        tile_grid.add (rockButton);
        tile_grid.add (waterButton);
        tile_grid.add (fishButton);
        stack.add_titled (tile_grid, "tile", "Tile");

        var building_grid = new Gtk.Grid ();
        building_grid.halign = Gtk.Align.CENTER;
        building_grid.row_spacing = 6;
        building_grid.column_spacing = 3;
        building_grid.margin_bottom = 6;
        building_grid.orientation = Gtk.Orientation.VERTICAL;
        roadButton = new Gtk.RadioButton (null);
        roadButton.tooltip_text = "Road";
        roadButton.image = new Gtk.Image.from_icon_name ("road-symbolic", Gtk.IconSize.LARGE_TOOLBAR);
        houseButton = new Gtk.RadioButton.from_widget (roadButton);
        houseButton.tooltip_text = "House";
        houseButton.image = new Gtk.Image.from_icon_name ("house-symbolic", Gtk.IconSize.LARGE_TOOLBAR);
        fountainButton = new Gtk.RadioButton.from_widget (roadButton);
        fountainButton.tooltip_text = "Fountain";
        fountainButton.image = new Gtk.Image.from_icon_name ("water-symbolic", Gtk.IconSize.LARGE_TOOLBAR);
        marketButton = new Gtk.RadioButton.with_label_from_widget (roadButton, "Market");
        farmButton = new Gtk.RadioButton.with_label_from_widget (roadButton, "Farm");
        prefectureButton = new Gtk.RadioButton.with_label_from_widget (roadButton, "Prefecture");
        engineerButton = new Gtk.RadioButton.with_label_from_widget (roadButton, "Engineer");

        building_grid.attach (houseButton, 0, 0, 1, 1);
        building_grid.attach (roadButton, 1, 0, 1, 1);
        building_grid.attach (fountainButton, 2, 0, 1, 1);
        building_grid.attach (marketButton, 0, 1, 3, 1);
        building_grid.attach (farmButton, 0, 2, 3, 1);
        building_grid.attach (prefectureButton, 0, 3, 3, 1);
        building_grid.attach (engineerButton, 0, 4, 3, 1);
        stack.add_titled (building_grid, "building", "Building");

        stack.notify["visible-child"].connect (() => {
            container.editMode = stack.visible_child == tile_grid ? 0 : 1;
        });

        grassButton.clicked.connect (() => {
            container.tileBrush = Tile.Terrain.GRASS;
        });

        forestButton.clicked.connect (() => {
                                          container.tileBrush = Tile.Terrain.FOREST;
                                      });

        farmableButton.clicked.connect (() => {
            container.tileBrush = Tile.Terrain.FARMABLE;
        });

        rockButton.clicked.connect (() => {
            container.tileBrush = Tile.Terrain.ROCK;
        });

        waterButton.clicked.connect (() => {
            container.tileBrush = Tile.Terrain.WATER;
        });

        fishButton.clicked.connect (() => {
            container.tileBrush = Tile.Terrain.FISH;
        });

        roadButton.clicked.connect (() => {
            container.buildingBrush = typeof(Road);
        });

        houseButton.clicked.connect (() => {
            container.buildingBrush = typeof(House);
        });

        fountainButton.clicked.connect (() => {
            container.buildingBrush = typeof(Fountain);
        });

        marketButton.clicked.connect (() => {
            container.buildingBrush = typeof(Market);
        });

        farmButton.clicked.connect (() => {
            container.buildingBrush = typeof(Farm);
        });

        prefectureButton.clicked.connect (() => {
            container.buildingBrush = typeof(Prefecture);
        });

        engineerButton.clicked.connect (() => {
            container.buildingBrush = typeof(Engineer);
        });

        grassButton.set_mode (false);
        forestButton.set_mode (false);
        farmableButton.set_mode (false);
        rockButton.set_mode (false);
        waterButton.set_mode (false);
        fishButton.set_mode (false);

        roadButton.set_mode (false);
        houseButton.set_mode (false);
        fountainButton.set_mode (false);
        marketButton.set_mode (false);
        farmButton.set_mode (false);
        prefectureButton.set_mode (false);
        engineerButton.set_mode (false);

        add (stack_switcher);
        add (stack);
    }
}
