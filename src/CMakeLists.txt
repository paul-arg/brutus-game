# make sure we have vala
find_package (Vala REQUIRED)
# make sure we use vala
include (ValaVersion)
# make sure it's the desired version of vala
ensure_vala_version ("0.16" MINIMUM)

file (GLOB VALA_FILES *.vala)

# files we want to compile
include (ValaPrecompile)
vala_precompile (VALA_C $ { EXEC_NAME }
                 $ { VALA_FILES }
                 PACKAGES
                 gtk + -3.0
                 OPTIONS
                 -- target - glib = 2.32
                                    -- thread
                 )

# tell cmake what to call the executable we just made
add_executable ($ { EXEC_NAME } $ { VALA_C })

# install the binaries we just made
install (TARGETS $ { EXEC_NAME } RUNTIME DESTINATION bin)