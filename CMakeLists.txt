cmake_minimum_required(VERSION 3.15)
project(platformer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

# TODO: Should be avoided
file(GLOB SRC_FILES
    "src/*.c"
    "src/**/*.c"
)

add_executable(platformer ${SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)
target_link_libraries(platformer PRIVATE PkgConfig::raylib)

add_custom_target(run
    COMMAND platformer
    DEPENDS platformer
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running MyProject..."
)