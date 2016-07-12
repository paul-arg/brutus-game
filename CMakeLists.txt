# project name
project (brutus)

# the oldest stable cmake version we support
cmake_minimum_required (VERSION 2.6)

# tell cmake where its modules can be found in our project directory
list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# where we install data directory (if we have any)
set (DATADIR "${CMAKE_INSTALL_PREFIX}/share")
set (BRUTUSDIR "${DATADIR}/brutus")

set (EXEC_NAME ${CMAKE_PROJECT_NAME})
set (RELEASE_NAME "conspiracy")
set (VERSION "0.1")

# we're about to use pkgconfig to make sure dependencies are installed so let's find pkgconfig first
find_package(PkgConfig)

# now let's actually check for the required dependencies
pkg_check_modules(DEPS REQUIRED gtk+-3.0)

add_definitions(${DEPS_CFLAGS})
add_definitions (-w)
link_libraries(${DEPS_LIBRARIES} m)
link_directories(${DEPS_LIBRARY_DIRS})

add_subdirectory (src)

# install our .desktop file so the Applications menu will see it
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/brutus.desktop DESTINATION ${DATADIR}/applications/)
file (GLOB SPRITES ${CMAKE_CURRENT_SOURCE_DIR}/data/sprites/*.svg)
file (GLOB MENUS ${CMAKE_CURRENT_SOURCE_DIR}/data/menus/*.svg)
install (FILES ${SPRITES} DESTINATION ${BRUTUSDIR}/sprites/)
install (FILES ${MENUS} DESTINATION ${BRUTUSDIR}/menus/)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/16x16/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/16x16/apps)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/24x24/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/24x24/apps)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/32x32/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/32x32/apps)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/48x48/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/48x48/apps)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/64x64/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/64x64/apps)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/128x128/brutus.svg DESTINATION ${DATADIR}/icons/hicolor/128x128/apps)
