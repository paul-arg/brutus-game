# project name
project (game)

# the oldest stable cmake version we support
cmake_minimum_required (VERSION 2.6)

# where we install data directory (if we have any)
set (DATADIR "${CMAKE_INSTALL_PREFIX}/share")

# what to call that directory where we install data too
set (PKGDATADIR "${DATADIR}/hello-again")

set (EXEC_NAME "gameapp")
set (RELEASE_NAME "Dayum so great")
set (VERSION "0.1")
set (VERSION_INFO "the fucking very beginning")

# we're about to use pkgconfig to make sure dependencies are installed so let's find pkgconfig first
find_package(PkgConfig)

# now let's actually check for the required dependencies
pkg_check_modules(DEPS REQUIRED gtkmm-3.0)

add_definitions(${DEPS_CFLAGS} -std=c++11)
link_libraries(${DEPS_LIBRARIES})
link_directories(${DEPS_LIBRARY_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file (GLOB CPP_FILES src/*.cpp)
file (GLOB HPP_FILES include/*.hpp)

# tell cmake what to call the executable we just made
add_executable(${EXEC_NAME} ${CPP_FILES} ${HPP_FILES})

# install the binaries we just made
install (TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)

# install our .desktop file so the Applications menu will see it
#install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/hello.desktop DESTINATION ${DATADIR}/applications/)
