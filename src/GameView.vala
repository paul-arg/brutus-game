public class GameView : Gtk.DrawingArea {
    private unowned MainWindow container;
    public int xIsoClick;
    public int yIsoClick;

    public GameView (MainWindow containerInput) {
        container = containerInput;
        events |= Gdk.EventMask.BUTTON_PRESS_MASK;
        events |= Gdk.EventMask.BUTTON_RELEASE_MASK;
    }

    public override bool draw (Cairo.Context cr) {
        if (container.game_map != null) {
            cr.set_line_width (3.0);

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

            cr.set_line_width (3.0);
            container.game_map.drawGrid (cr);
        }

        return true;
    }

    public override bool button_press_event (Gdk.EventButton event) {
        xIsoClick = screenToIsoX ((int)event.x, (int)event.y, TILE_HEIGHT, TILE_WIDTH, container.game_map.mapHeight * TILE_WIDTH, 0);
        yIsoClick = screenToIsoY ((int)event.x, (int)event.y, TILE_HEIGHT, TILE_WIDTH, container.game_map.mapHeight * TILE_WIDTH, 0);
        /*
         * message(@"    clicked at $(event.x) ,$(event.y)");
         * message(@"    clicked at iso $xIsoClick ,$yIsoClick");
         */

        return true;
    }

    public override bool button_release_event (Gdk.EventButton event) {
        int xIsoRelease = screenToIsoX ((int)event.x, (int)event.y, TILE_HEIGHT, TILE_WIDTH, container.game_map.mapHeight * TILE_WIDTH, 0);
        int yIsoRelease = screenToIsoY ((int)event.x, (int)event.y, TILE_HEIGHT, TILE_WIDTH, container.game_map.mapHeight * TILE_WIDTH, 0);

        /*
         * cout << "    released at " << (int) event.x << ", " << (int) event.y << endl;
         * cout << "    released at iso " << xIso << ", " << yIso << endl;
         */
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
                container.game_map.buildArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease, container.buildingBrush);
            }

            if (event.button == 3) {
                container.game_map.destroyArea (xIsoClick, yIsoClick, xIsoRelease, yIsoRelease);
            }
        }

        return true;
    }
}

public static int screenToIsoX (int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY) {
    return (int)Math.floor (((double)(-offsetX * tileHeight + xScreen * tileHeight - offsetY * tileWidth + tileWidth * yScreen)) / ((double)(2 * tileWidth * tileHeight)));
}

public static int screenToIsoY (int xScreen, int yScreen, int tileHeight, int tileWidth, int offsetX, int offsetY) {
    return (int)Math.floor (((double)(offsetX * tileHeight - xScreen * tileHeight - offsetY * tileWidth + tileWidth * yScreen)) / ((double)(2 * tileWidth * tileHeight)));
}

/* upper corner of the tile */
public static int isoToScreenX (int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY) {
    return xIso * tileWidth - yIso * tileWidth + offsetX;
}

public static int isoToScreenY (int xIso, int yIso, int tileHeight, int tileWidth, int offsetX, int offsetY) {
    return xIso * tileHeight + yIso * tileHeight + offsetY;
}