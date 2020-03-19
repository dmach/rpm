# use any sources found under the current directory
#file(GLOB SOURCES *.c)
list(APPEND SOURCES rpmgensig.c)


# build librpmsign.so
add_library(librpmsign SHARED ${SOURCES})
set_target_properties(librpmsign PROPERTIES OUTPUT_NAME "rpmsign")
set_target_properties(librpmsign PROPERTIES SOVERSION ${RPM_SO_VERSION})


# install librpmbuild.so
install(TARGETS librpmsign LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
