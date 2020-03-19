# use any sources found under the current directory
file(GLOB SOURCES l*.c)


# allow including LUAEXT_SOURCES in the parent scope
set(LUAEXT_SOURCES ${SOURCES} PARENT_SCOPE)
