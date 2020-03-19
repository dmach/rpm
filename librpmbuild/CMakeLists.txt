# use any sources found under the current directory
file(GLOB SOURCES *.c)


list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../misc/fts.c)


# build librpmbuild.so
add_library(librpmbuild SHARED ${SOURCES})
set_target_properties(librpmbuild PROPERTIES OUTPUT_NAME "rpmbuild")
set_target_properties(librpmbuild PROPERTIES SOVERSION ${RPM_SO_VERSION})


# no pkgconf, manually link by name
target_link_libraries(librpmbuild magic)


# elfutils
pkg_check_modules(LIBDW REQUIRED libdw)
target_link_libraries(librpmbuild ${LIBDW_LIBRARIES})


# install librpmbuild.so
install(TARGETS librpmbuild LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
