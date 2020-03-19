# use any sources found under the current directory
file(GLOB SOURCES *.c)


# remove all crypto
list(FILTER SOURCES EXCLUDE REGEX "/digest_.*\.c$")


# add luaext sources
message("SOURCES ${LUAEXT_SOURCES}")
list(APPEND SOURCES ${LUAEXT_SOURCES})


# return requested crypto back
if(WITH_BEECRYPT)
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/digest_beecrypt.c)
elseif(WITH_OPENSSL)
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/digest_openssl.c)
elseif(WITH_LIBGCRYPT)
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/digest_libgcrypt.c)
elseif(WITH_LIBGCRYPT)
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/digest_libgcrypt.c)
else()
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/digest_nss.c)
endif()


# build librpmio.so
add_library(librpmio SHARED ${SOURCES})
set_target_properties(librpmio PROPERTIES OUTPUT_NAME "rpmio")
set_target_properties(librpmio PROPERTIES SOVERSION ${RPM_SO_VERSION})


# link crypto packages
if(WITH_BEECRYPT)
elseif(WITH_OPENSSL)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(librpmio ${OPENSSL_CRYPTO_LIBRARY})
elseif(WITH_LIBGCRYPT)
elseif(WITH_LIBGCRYPT)
else()
endif()


pkg_check_modules(LUA REQUIRED lua)
target_link_libraries(librpmio ${LUA_LIBRARIES})


# install librpmio.so
install(TARGETS librpmio LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
