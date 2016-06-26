public class Brutus.GameView : Gtk.DrawingArea {
    private unowned Brutus.MainWindow container;
    public int xIsoClick;
    public int yIsoClick;
    public int xIsoRelease;
    public int yIsoRelease;
    public double xIsoRelease_double;
    public double yIsoRelease_double;

    public GameView (MainWindow containerInput) {
        container = containerInput;
        events |= Gdk.EventMask.BUTTON_PRESS_MASK;
        events |= Gdk.EventMask.BUTTON_RELEASE_MASK;
        events |= Gdk.EventMask.POINTER_MOTION_MASK;
    }

    public override bool draw (Cairo.Context cr) {
        int width = get_allocated_width ();
        int height = get_allocated_height ();

        cr.set_source_rgb (0, 0, 0);
        cr.rectangle (0, 0, width, height);
        cr.fill_preserve ();
        if (container.game_map != null) {
            cr.set_line_width (3.0);
            container.game_map.drawGrid (cr);
            for (int i = 0; i < container.game_map.mapWidth; i++) {
                for (int j = 0; j < container.game_map.mapHeight; j++) {
                    if (container.game_map.getTile (i, j) != null) {
                        container.game_map.getTile (i, j).draw (cr);

                        if (container.game_map.getTile (i, j).building != null) {
                            container.game_map.getTile (i, j).building.draw (cr);
                        }
                    }
                }
            }
        }

        return true;
    }

    public override bool button_press_event (Gdk.EventButton event) {
        xIsoClick = (int)Math.floor (screenToIsoX (event.x, event.y));
        yIsoClick = (int)Math.floor (screenToIsoY (event.x, event.y));
        /*
         * message(@"    clicked at $(event.x) ,$(event.y)");
         * message(@"    clicked at iso $xIsoClick ,$yIsoClick");
         */

        return true;
    }

    public override bool button_release_event (Gdk.EventButton event) {
        xIsoRelease = (int)Math.floor (screenToIsoX (event.x, event.y));
        yIsoRelease = (int)Math.floor (screenToIsoY (event.x, event.y));
        xIsoRelease_double = screenToIsoX (event.x, event.y);
        yIsoRelease_double = screenToIsoY (event.x, event.y);

        warning("release %f, %f", xIsoRelease_double, yIsoRelease_double);

        if (container.editMode == 0) {
            if (event.button == 1) {
                container.game_map.newTileArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease, container.tileBrush);
            }

            if (event.button == 3) {
                container.game_map.deleteTileArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
            }
        }

        if (container.editMode == 1) {
            if (event.button == 1) {
                if (container.buildingBrush == typeof(Brutus.Road)) {
                    L_path(xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
                } else {
                container.game_map.buildArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease, container.buildingBrush);
                }
            }

            if (event.button == 3) {
                container.game_map.destroyArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
            }
        }

        if (is_right_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){
            warning("right mid");}
        if (is_left_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){
            warning("left mid");}
        if (is_up_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){
            warning("up mid");}
        if (is_down_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){
            warning("down mid");}

        return true;
    }

    public override bool motion_notify_event (Gdk.EventMotion event) {
        var width = get_allocated_width ();
        var height = get_allocated_height ();
        if (event.x < 5) {
            warning ("Scroll left");
        } else if (width - event.x < 5) {
            warning ("Scroll right");
            warning ("Scroll right");
        }

        if (event.y < 5) {
            warning ("Scroll up");
        } else if (height - event.y < 5) {
            warning ("Scroll down");
        }

        return true;
    }

    public void L_path(int x1, int y1, int x2, int y2) {
        int xm = int.min(x1, x2);
        int xM = int.max(x1, x2);
        int ym = int.min(y1, y2);
        int yM = int.max(y1, y2);

        if (((x1 == xM && y1 == yM) || (x2 == xM && y2 == yM)) && is_right_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)) { //>path
            container.game_map.buildArea (xm, ym, xM, ym, container.buildingBrush);
            container.game_map.buildArea (xM, ym, xM, yM, container.buildingBrush);
            warning(">");
        }
        else if (((x1 == xM && y1 == yM) || (x2 == xM && y2 == yM)) && is_left_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){ //<path
            container.game_map.buildArea (xm, ym, xm, yM, container.buildingBrush);
            container.game_map.buildArea (xm, yM, xM, yM, container.buildingBrush);
             warning("<");
        }
        else if (!((x1 == xM && y1 == yM) || (x2 == xM && y2 == yM)) && is_up_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)) { //^path
            container.game_map.buildArea (xm, yM, xm, ym, container.buildingBrush);
            container.game_map.buildArea (xm, ym, xM, ym, container.buildingBrush);
            warning("^");
        }
        else if (!((x1 == xM && y1 == yM) || (x2 == xM && y2 == yM)) && is_down_mid(xIsoRelease_double - xIsoRelease, yIsoRelease_double - yIsoRelease)){ //vpath
            container.game_map.buildArea (xm, yM, xM, yM, container.buildingBrush);
            container.game_map.buildArea (xM, yM, xM, ym, container.buildingBrush);
            warning("v");
        }
    }
}

public bool is_left_mid(double x, double y) {
    return x > 0 && y < 1 && y > x;
}

public bool is_right_mid(double x, double y) {
    return x < 1 && y > 0 && y < x;
}

public bool is_up_mid(double x, double y) {
    return x > 0 && y > 0 && y < - x + 1;
}

public bool is_down_mid(double x, double y) {
    return x < 1 && y < 1 && y > - x + 1;
}

public int bijectionX(int n, int width) {
    return n % width;
}

public int bijectionY(int n, int width) {
    return n - (n % width);
}

public static double screenToIsoX (double xScreen, double yScreen, int tileHeight = TILE_HEIGHT, int tileWidth = TILE_WIDTH, int offsetX = OFFSET_X, int offsetY = OFFSET_Y) {
    return ((double)(-offsetX * tileHeight + xScreen * tileHeight - offsetY * tileWidth + tileWidth * yScreen)) / ((double)(2 * tileWidth * tileHeight));
}

public static double screenToIsoY (double xScreen, double yScreen, int tileHeight = TILE_HEIGHT, int tileWidth = TILE_WIDTH, int offsetX = OFFSET_X, int offsetY = OFFSET_Y) {
    return ((double)(offsetX * tileHeight - xScreen * tileHeight - offsetY * tileWidth + tileWidth * yScreen)) / ((double)(2 * tileWidth * tileHeight));
}

/* upper corner of the tile */
public static int isoToScreenX (int xIso, int yIso, int tileHeight = TILE_HEIGHT, int tileWidth = TILE_WIDTH, int offsetX = OFFSET_X, int offsetY = OFFSET_Y) {
    return xIso * tileWidth - yIso * tileWidth + offsetX;
}

public static int isoToScreenY (int xIso, int yIso, int tileHeight = TILE_HEIGHT, int tileWidth = TILE_WIDTH, int offsetX = OFFSET_X, int offsetY = OFFSET_Y) {
    return xIso * tileHeight + yIso * tileHeight + offsetY;
}
