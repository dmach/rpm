message("Running CMake on rpm...")
cmake_minimum_required(VERSION 3.5)


include(VERSION.cmake)
project(libdnf LANGUAGES C VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
cmake_policy(VERSION ${CMAKE_VERSION})


message("Building ${PROJECT_NAME} version ${PROJECT_VERSION}")


if(DEFINED PACKAGE_VERSION)
    if(NOT ${PACKAGE_VERSION} STREQUAL ${PROJECT_VERSION})
        message(FATAL_ERROR "Variables PROJECT_VERSION and PACKAGE_VERSION differ. Make sure the versions in VERSION.cmake and the value provided via -DPACKAGE_VERSION are in sync.")
    endif()
endif()

option(WITH_LUA "" ON)


# build options - compression
option(WITH_ZSTD "Build with zstd support" ON)

# build options - crypto
option(WITH_LIBGCRYPT "" OFF)
option(WITH_NSS "" OFF)
option(WITH_BEECRYPT "" OFF)
option(WITH_OPENSSL "Build with OpenSSL crypto support" ON)

# build options - rpmdb
option(WITH_RPMDB_BDB "Build with Berkeley DB rpm database format support" ON)
option(WITH_RPMDB_BDB_RO "Build with built-in read-only Berkeley DB support (EXPERIMENTAL)" OFF)
option(WITH_RPMDB_NDB "Build with New DataBase rpm database format support" ON)
option(WITH_RPMDB_SQLITE "Build with New DataBase rpm database format support" ON)


# build options - bindings
option(WITH_PYTHON2 "Build Python 2 bindings" OFF)
option(WITH_PYTHON3 "Build Python 3 bindings" ON)

# build options - debugging
option(WITH_SANITIZERS "Build with address, leak and undefined sanitizers (DEBUG ONLY)" OFF)


# includes
include(GNUInstallDirs)


# common dependencies
find_package(PkgConfig REQUIRED)

pkg_check_modules(POPT REQUIRED popt)


# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# warnings
#add_compile_options(-Wall -Wextra -Werror)
#add_compile_options(-Wcast-align -Wformat-nonliteral -Wmissing-format-attribute -Wredundant-decls -Wsign-compare -Wtype-limits -Wuninitialized -Wwrite-strings)
# not sure about the conversion warnings being errors; review later
#add_compile_options(-Wconversion)


if(WITH_SANITIZERS)
    message(WARNING "Building with sanitizers enabled!")
    set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=leak -fsanitize=undefined")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # requires: compiler-rt package on Fedora
        set(SANITIZER_FLAGS "${SANITIZER_FLAGS} -static-libsan")
    else()
        set(SANITIZER_FLAGS "${SANITIZER_FLAGS} -static-libasan -static-liblsan -static-libubsan")
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SANITIZER_FLAGS}")
endif()



set(RPM_SO_VERSION 9.0.0)


include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")


add_subdirectory("luaext")

add_subdirectory("librpm")
add_subdirectory("librpmio")
add_subdirectory("librpmbuild")
add_subdirectory("librpmsign")

add_subdirectory("bin")

## libdnf
#add_subdirectory("include")
#add_subdirectory("libdnf")
#add_subdirectory("libdnf-cli")
#add_subdirectory("doc")
#add_subdirectory("bindings")
#
## dnfdaemon
#add_subdirectory("dnfdaemon-server")
#add_subdirectory("dnfdaemon-client")
#
## microdnf
#add_subdirectory("microdnf")
#
## tests
#enable_testing()
#add_subdirectory("test")
