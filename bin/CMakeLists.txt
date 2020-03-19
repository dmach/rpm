# rpm
add_executable(rpm rpm.c ../misc/cliutils.c)
target_link_libraries(rpm librpm)
target_link_libraries(rpm librpmio)
target_link_libraries(rpm ${POPT_LIBRARIES})
install(TARGETS rpm RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpm2archive
add_executable(rpm2archive rpm2archive.c ../misc/cliutils.c)
target_link_libraries(rpm2archive librpm)
target_link_libraries(rpm2archive librpmio)
target_link_libraries(rpm2archive ${POPT_LIBRARIES})

pkg_check_modules(LIBARCHIVE REQUIRED libarchive)
target_link_libraries(rpm2archive ${LIBARCHIVE_LIBRARIES})

install(TARGETS rpm2archive RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpm2cpio
add_executable(rpm2cpio rpm2cpio.c ../misc/cliutils.c)
target_link_libraries(rpm2cpio librpm)
target_link_libraries(rpm2cpio librpmio)
target_link_libraries(rpm2cpio ${POPT_LIBRARIES})
install(TARGETS rpm2cpio RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpmbuild
add_executable(rpmbuild rpmbuild.c ../misc/cliutils.c)
target_link_libraries(rpmbuild librpm)
target_link_libraries(rpmbuild librpmbuild)
target_link_libraries(rpmbuild librpmio)
target_link_libraries(rpmbuild ${POPT_LIBRARIES})
install(TARGETS rpmbuild RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpmdb
add_executable(rpmdb rpmdb.c ../misc/cliutils.c)
target_link_libraries(rpmdb librpm)
target_link_libraries(rpmdb librpmio)
target_link_libraries(rpmdb ${POPT_LIBRARIES})
install(TARGETS rpmdb RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpmkeys
add_executable(rpmkeys rpmkeys.c ../misc/cliutils.c)
target_link_libraries(rpmkeys librpm)
target_link_libraries(rpmkeys librpmio)
target_link_libraries(rpmkeys ${POPT_LIBRARIES})
install(TARGETS rpmkeys RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpmsign
add_executable(rpmsign rpmsign.c ../misc/cliutils.c)
target_link_libraries(rpmsign librpm)
target_link_libraries(rpmsign librpmio)
target_link_libraries(rpmsign librpmsign)
target_link_libraries(rpmsign ${POPT_LIBRARIES})
install(TARGETS rpmsign RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# rpmspec
add_executable(rpmspec rpmspec.c ../misc/cliutils.c)
target_link_libraries(rpmspec librpm)
target_link_libraries(rpmspec librpmbuild)
target_link_libraries(rpmspec librpmio)
target_link_libraries(rpmspec ${POPT_LIBRARIES})
install(TARGETS rpmspec RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
