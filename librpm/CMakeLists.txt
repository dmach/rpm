# AWK=awk ./gentagtbl.sh ../include/rpm/rpmtag.h  > tagtbl.C


# use any sources found under the current directory
file(GLOB SOURCES *.c)


set(SOURCES
    ${SOURCES}
    backend/dbi.c
    backend/dbiset.c
    backend/dummydb.c
)


# build librpm.so
add_library(librpm SHARED ${SOURCES})
set_target_properties(librpm PROPERTIES OUTPUT_NAME "rpm")
set_target_properties(librpm PROPERTIES SOVERSION ${RPM_SO_VERSION})


# install librpm.so
install(TARGETS librpm LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})


# link libraries and set pkg-config requires

pkg_check_modules(POPT REQUIRED popt)
target_link_libraries(librpm ${POPT_LIBRARIES})

if(WITH_SQLITE)
    pkg_check_modules(SQLITE3 REQUIRED sqlite3)
    target_link_libraries(librpm ${SQLITE3_LIBRARIES})
endif()
