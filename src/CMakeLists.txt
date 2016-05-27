# make sure we have vala
find_package (Vala REQUIRED)
# make sure we use vala
include (ValaVersion)
# make sure it's the desired version of vala
ensure_vala_version ("0.16" MINIMUM)

configure_file (${CMAKE_SOURCE_DIR}/config.vala.cmake ${CMAKE_BINARY_DIR}/config.vala)

# files we want to compile
include (ValaPrecompile)
vala_precompile (VALA_C ${EXEC_NAME}
        ${CMAKE_BINARY_DIR}/config.vala
        Const.vala
        GameView.vala
        InGameGUI.vala
        MainWindow.vala
        Map.vala
        Tile.vala
        Building/Building.vala
        Building/Fountain.vala
        Building/House.vala
    PACKAGES
        gtk+-3.0
    OPTIONS
        --target-glib=2.32
        --thread
)

# tell cmake what to call the executable we just made
add_executable (${EXEC_NAME} ${VALA_C})

# install the binaries we just made
install (TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
