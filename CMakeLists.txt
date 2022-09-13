cmake_minimum_required(VERSION 3.17)
project(RogueLinuxCpp)

# Define either of KEYS_QWERTY or KEYS_DVORAK below
add_definitions(-DKEYS_QWERTY)

include_directories(include)

set(COMPILER_FLAGS "-O3")

add_library(rogue_lib STATIC
        src/xcrypt.c
        src/wizard.c
        src/weapons.c
        src/vers.c
        src/things.c
        src/sticks.c
        src/state.c
        src/scrolls.c
        src/save.c
        src/rooms.c
        src/rip.c
        src/rings.c
        src/potions.c
        src/passages.c
        src/pack.c
        src/options.c
        src/new_level.c
        src/move.c
        src/monsters.c
        src/misc.c
        src/mdport.c
        src/mach_dep.c
        src/list.c
        src/io.c
        src/init.c
        src/fight.c
        src/extern.c
        src/daemons.c
        src/daemon.c
        src/command.c
        src/chase.c
        src/armor.c
)

set_target_properties(rogue_lib PROPERTIES LINKER_LANGUAGE C)
target_compile_options(rogue_lib PRIVATE ${COMPILER_FLAGS})

add_executable(rogue 
        src/main.c
)

#   ncourses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(rogue rogue_lib ${CURSES_LIBRARIES})
# -------------------

set_target_properties(rogue PROPERTIES LINKER_LANGUAGE C)
target_compile_options(rogue PRIVATE ${COMPILER_FLAGS})
